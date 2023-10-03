/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef CYAPICALLBACKS_H
#define CYAPICALLBACKS_H
    

    /*Define your macro callbacks here */
    
 #define CAN_RECEIVE_MSG_CALLBACK
 #define CAN_ReceiveMsg_Callback() can_rx_basic_cb(rxMailbox)
    
    /*For more information, refer to the Writing Code topic in the PSoC Creator Help.*/

    
#endif /* CYAPICALLBACKS_H */   
/* [] */
