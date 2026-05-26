/**
 * \file 	vI2C.c
 * \author 	Thomas Barth	- Hochschule Darmstadt thomas.barth@h-da.de
 * \date 	25.06.2017
 * \version	0.2
 *
 * \brief virtualI2C queue interface without OS
 *
 * \copyright Copyright ©2016
 * Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
 * Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
 * (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
 * this paragraph and the following paragraph appear in all copies, modifications, and distributions.
 * Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
 *
 * \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
 * The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
 * This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
 */


#include "logging.h"
#include <stdlib.h>

#include "vI2C_noOS.h"
#include "vI2C_cfg.h"


/** \brief Module API concationation with #CFG_I2C_MODULE. */
#define MODULE(x)       PPCAT(CFG_I2C_MODULE, x)

//I2C state machine
vI2C_state_t __vI2C_state;

//I2C Ringbuffer type
typedef struct{
    uint8_t     fill;
    uint8_t     read;
    uint8_t     write;
    vI2C_msg_t  buf[CFG_I2C_QUEUE_L];  //buffer is on the stack
}vI2C_RB_t;

//ringbuffer
vI2C_RB_t  vI2C__RB;

//local prototypes
static RC_t vI2C__send_HW();
static void vI2C_done_hdl();

RC_t vI2C_init(){
    
    //Start OLED I2C
    MODULE(Start)();
    
    //set state
    __vI2C_state=vI2C_state_idle;
    
    //init ringbuffer
    vI2C__RB.fill=0;
    vI2C__RB.read=0;
    vI2C__RB.write=0;
    
    return RC_SUCCESS;
}

RC_t vI2C_send(uint8_t slaveAddress, uint8_t* p_data, uint8_t cnt, vI2C_flags_t flags, void (*p_callback)(vI2C_msg_t), void* p_usr_data){
                
    //check I2C state
    if(MODULE(initVar)!=1)
        return RC_ERROR_INVALID_STATE;
    
    //data container check
    if(p_data==NULL)
        return RC_ERROR_BAD_PARAM;
    
    //flag check
    if(!(!(flags&vI2C_FLAG_READ)^!(flags&vI2C_FLAG_WRITE)))
        return RC_ERROR_BAD_PARAM;
    
    //check if RB can save request
    if(vI2C__RB.fill>=CFG_I2C_QUEUE_L)
        return RC_ERROR_BUFFER_FULL;
    
    //Write to ringbuffer
    vI2C__RB.buf[vI2C__RB.write]=(vI2C_msg_t){
        slaveAddress,
        p_data,
        cnt,
        0,
        flags,
        transmission_PENDING,
        p_callback,
        p_usr_data 
    };
    
    //increase index
    vI2C__RB.write=(++vI2C__RB.write)%CFG_I2C_QUEUE_L;
    
    //increase fill level
    vI2C__RB.fill++;
    
    //if the buffer has only 1 element and the current state is idle, we trigger the HW
    if(vI2C__RB.fill==1&&__vI2C_state==vI2C_state_idle)
        return vI2C__send_HW();
    else
        return RC_SUCCESS;
    
}
RC_t vI2C__send_HW(){
    
    vI2C_msg_t* msg = &vI2C__RB.buf[vI2C__RB.read];
        
    //update message state
    msg->state=transmission_ACTIVE;
        
    //send frame to I2C HW
    if(msg->flags&vI2C_FLAG_WRITE){
        //set state for writing
        __vI2C_state=vI2C_state_writing;
        
        //write frame to I2C Module
        MODULE(MasterWriteBuf)(msg->slaveAddress,msg->p_data+msg->transfered,msg->cnt,MODULE(MODE_COMPLETE_XFER));
    }
    else if(msg->flags&vI2C_FLAG_READ){
        //set state for reading
        __vI2C_state=vI2C_state_receiving;
        
        //receive frame from I2C Module
        MODULE(MasterReadBuf)(msg->slaveAddress,msg->p_data+msg->transfered,msg->cnt,MODULE(MODE_COMPLETE_XFER));
    }
    else{
        //set state to idle
         __vI2C_state=vI2C_state_idle;
        
        //update message state
        msg->state=transmission_ABORTED;
            
        //decrease fill level
        vI2C__RB.fill--;
    
        //increase index
        vI2C__RB.read=(++vI2C__RB.read)%CFG_I2C_QUEUE_L;
        
        //call callback
        if(msg->p_callback!=NULL)
            msg->p_callback(*msg);
            
       //free memory if requested by the user
        if(msg->flags&vI2C_FLAG_FREE_M&&(msg->flags&vI2C_FLAG_WRITE))                
            free(msg->p_data);
    
        //check if there are more messages waiting
        if(vI2C__RB.fill!=0)
            vI2C__send_HW();        
    }
    
    return RC_SUCCESS;
}

void vI2C_done_hdl(){

    vI2C_msg_t* msg = &vI2C__RB.buf[vI2C__RB.read];
    
    if(vI2C__RB.fill!=0){
        //decrease fill level
        vI2C__RB.fill--;
    
        //increase index
        vI2C__RB.read=(++vI2C__RB.read)%CFG_I2C_QUEUE_L;
        
        //set state to idle
         __vI2C_state=vI2C_state_idle;
        
        //check for bus errors
        if(MODULE(MasterClearStatus)()&(MODULE(MSTAT_ERR_SHORT_XFER)|MODULE(MSTAT_ERR_ADDR_NAK)|MODULE(MSTAT_ERR_ARB_LOST)|MODULE(MSTAT_ERR_XFER))){
            //update message state
            msg->state=transmission_ERROR;                  
        }
        else{
            //increment number of transfered bytes
            msg->transfered+=msg->cnt;
            
            //update message state
            msg->state=transmission_COMPLETED;            
        }
        
        //call callback
        if(msg->p_callback!=NULL)
            msg->p_callback(*msg);
            
       //free memory if requested by the user
        if(msg->flags&vI2C_FLAG_FREE_M&&(msg->flags&vI2C_FLAG_WRITE))                
            free(msg->p_data);
    
        //check if there are more messages waiting
        if(vI2C__RB.fill!=0)
            vI2C__send_HW();
    }
}

void vI2C_ISR(){
    
    //check for complete flags, depending on the direction of transfer
    switch(__vI2C_state){                                                           
    case vI2C_state_receiving:                                                      
        if(MODULE(mstrStatus)&MODULE(MSTAT_RD_CMPLT))                                           
            vI2C_done_hdl();                                       
        break;                                                                      
    case vI2C_state_writing:                                                        
        if(MODULE(mstrStatus)&MODULE(MSTAT_WR_CMPLT))                                           
            vI2C_done_hdl();                                       
        break;                                                                      
    default:                                                                        
        /*this is an error condition, as there can be no interrupt during idle state. (at least in theory...)*/
        break;                                                                      
    }                                                                                
    
    return;
}

/* [] END OF FILE */