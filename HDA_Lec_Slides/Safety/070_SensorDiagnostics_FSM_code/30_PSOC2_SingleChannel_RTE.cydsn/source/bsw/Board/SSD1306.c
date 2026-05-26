/**
 * \file 	SSD1306.c
 * \author 	Thomas Barth	- Hochschule Darmstadt thomas.barth@h-da.de
 * \date 	09.07.2017
 *
 * \brief SSD1306 Driver
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

//-------------------------------------------------------------------- [Includes]
#include "SSD1306.h"
#include "vI2C_cfg.h"
#include "ASCII_char.h"
#include "logging.h"
#include "vI2C_noOS.h"


#if (OS==OS_FREERTOS)
    #include "task.h"
#endif

//-------------------------------------------------------------------- [Definitions]
#define SSD1306_CMD_FLAG    (0<<6)      /**< \brief Indicates that this is a command frame. */
#define SSD1306_DATA_FLAG   (1<<6)      /**< \brief Indicates that this is a data frame. */

//-------------------------------------------------------------------- [Types]
/**
 * \brief SSD1306 Commands
 *
 * The commands are send via the I2C Interface with command flag set
 */
typedef enum{
    SSD1306_CMD_SET_CONTRAST    = 0x81, /**< Double byte command to select 1 out of 256 contrast steps. Contrast increases as the value increases.   */
    SSD1306_CMD_DISPLAY_ON_RAM  = 0xa4, /**< Resume to RAM content display (RESET) Output follows RAM content . */
    SSD1306_CMD_DISPLAY_ON_NRAM = 0xa5, /**< Entire display ON Output ignores RAM content  */
    SSD1306_CMD_NORMAL_MODE     = 0xa6, /**< A 1 in RAM is a ON on the display  */
    SSD1306_CMD_INVERSE_MODE    = 0xa7, /**< A 1 in RAM is a OFF on the Display */
    SSD1306_CMD_DISPLAY_OFF     = 0xae, /**< Display off (sleep mode). */
    SSD1306_CMD_DISPLAY_ON      = 0xaf, /**< Display on. */
    SSD1306_CMD_SCROLL_RIGHT    = 0x26, /**< 7 Byte command. Continuous horizontal scroll to the right. */
    SSD1306_CMD_SCROLL_LEFT     = 0x27, /**< 7 Byte command. Continuous horizontal scroll to the left. */
    SSD1306_CMD_SCROLL_V_RIGHT  = 0x29, /**< 6 Byte command. Continuous Vertical and Right Horizontal Scroll. */
    SSD1306_CMD_SCROLL_V_LEFT   = 0x2a, /**< 6 Byte command. Continuous Vertical and Left Horizontal Scroll. */
    SSD1306_CMD_SCROLL_STOP     = 0x2e, /**< Stop scrolling that is configured by command 26h/27h/29h/2Ah. . */
    SSD1306_CMD_SCROLL_START    = 0x2f, /**< Start scrolling that is configured by the scrolling setup commands :26h/27h/29h/2Ah */
     
    SSD1306_CMD_SCROLL_V_AREA   = 0xa3, /**< 3 Byte command: Set Vertical Scroll Area. */
    SSD1306_CMD_SET_ADR_MODE    = 0x20, /**< 2 Byte command: Set Memory Addressing Mode. */
    SSD1306_CMD_SET_C_ADR       = 0x21, /**< 3 Byte command: Set Column Address. */
    SSD1306_CMD_SET_P_ADR       = 0x22, /**< 3 Byte command: Set Page Address. */
    SSD1306_CMD_CHR_PMP         = 0x8d, /**< 2 Byte command: Charge Pump settings. */
    
    SSD1306_CMD_SET_SEG_M_0     = 0xa0, /**< Column adr 0 is mapped to SEG0 */
    SSD1306_CMD_SET_SEG_M_127   = 0xa1, /**< Column adr 0 is mapped to SEG127 */
    SSD1306_CMD_SET_MUX_RATIO   = 0xa8, /**< 2 Byte command: Set Multiplexer ratio. */
    SSD1306_CMD_SET_COM_DIR_N   = 0xc0, /**< Normal Mode COM 0 to COM N-1. */
    SSD1306_CMD_SET_COM_DIR_R   = 0xc8, /**< Remapped Mode COM N-1 to COM 0. */
    SSD1306_CMD_SET_OFF         = 0xd3, /**< 2 Byte command: Set Display offset. */
    SSD1306_CMD_SET_COM_PIN     = 0xda, /**< 2 Byte command: Set COM Pins Hardware Cfg. */
    SSD1306_CMD_SET_CLOCK       = 0xd5, /**< 2 Byte command: Set Column Address. */
    SSD1306_CMD_SET_CRG_PERIODE = 0xd9, /**< 2 Byte command: Set Pre-Charge Periode. */
    SSD1306_CMD_SET_VCOMH       = 0xdb, /**< 2 Byte command: Set Vcomh Level. */
    SSD1306_CMD_NOP             = 0xe3, /**< No Operation. */
    
    SSD1306_CMDM_CA_L           = 0x0F, /**< Command mask set lower column address. */
    SSD1306_CMDM_CA_H           = 0x10, /**< Command mask set higher column address. */
    SSD1306_CMDM_RA             = 0xB0, /**< Command mask set row address. */
}SSD1306_CMD_t;

/**
 * \brief SSD1306 Instruction types
 */
typedef enum{
    SSD1306_INST_DATA           =0,     /**< Instruction contains data. */
    SSD1306_INST_CMD            =1      /**< Instruction contains a command. */
}SSD_ins_t;

/**
 * \brief SSD1306 Instruction ringbuffer type
 */
typedef struct{
    uint8_t idx;                        /**< \brief rinbuffer index */
    uint8_t data[CFG_I2C_QUEUE_L][2];   /**< \brief rinbuffer data */
}_SSD1306_irb_t;

//-------------------------------------------------------------------- [Const data]
/**
 * \brief SSD1306 Initialization Commands
 */
const uint8_t init_cmd_array[]={
    SSD1306_CMD_DISPLAY_OFF,	        // DISPLAY OFF AEh, X[0]=0b:Display OFF (sleep mode) (RESET) 
	SSD1306_CMD_SET_CLOCK,	            // START: SET OSC FREQUENY Define the divide ratio (D) of the display clocks (DCLK): Divide ratio= A[3:0] + 1, RESET is 0000b (divide ratio = 1)
	0x80,			                    // WRITE:  Set the Oscillator Frequency, F OSC . Oscillator Frequency increases with  the value of A[7:4] and vice versa.  RESET is 1000b Range:0000b~1111b 
    SSD1306_CMD_SET_MUX_RATIO,	        // START: SET MUX RATIO Set MUX ratio to N+1 MUX N=A[5:0] : from 16MUX to 64MUX, RESET= 111111b (i.e. 63d, 64MUX) 
	0x3F,			                    // WRITE 64MUX A[5:0] 
	SSD1306_CMD_SET_OFF,		        // START: SET DISPLAY OFFSET
	0x00,			                    // offset = 0 Set vertical shift by COM from 0d~63d The value is reset to 00h after RESET. 
	0x40,			                    // set display start line, start line = 0 0b01xxxxxx
	SSD1306_CMD_CHR_PMP,		        // START: Charge Pump Setting 
	0x14,			                    // A[7:0] *  *  0  1  0  A[2] 0  0; A[2] = 0b, Disable charge pump(RESET) A[2] = 1b, Enable charge pump during display on 
	SSD1306_CMD_SET_ADR_MODE,	        // SET MEMORY ADDRESSING MODE
	0x02,			                    // horizontal addressing mode
	SSD1306_CMD_SET_SEG_M_127,	        // set segment re-map, column address 127 is mapped to SEG0
	SSD1306_CMD_SET_COM_DIR_R,	        // set COM/Output scan direction, remapped mode (COM[N-1] to COM0)
	SSD1306_CMD_SET_COM_PIN,	        // SET COM PINS HARDWARE CONFIGURATION
	0x12,			                    // alternative COM pin configuration 
	SSD1306_CMD_SET_CONTRAST,	        // SET CONTRAST CONTROL
	0xCF,			                    // Contrast 
	SSD1306_CMD_SET_CRG_PERIODE,        // SET PRE CHARGE PERIOD
	0xF1,			                    // 
	SSD1306_CMD_SET_VCOMH,		        // SET V_COMH DESELECT LEVEL
	0x40,			                    // 
	SSD1306_CMD_DISPLAY_ON_RAM,	        // DISABLE ENTIRE DISPLAY ON
	SSD1306_CMD_NORMAL_MODE,	        // NORMAL MODE (A7 for inverse display)
	SSD1306_CMD_DISPLAY_ON              // DISPLAY ON
};			

/**
 * \brief SSD1306 Instruction ringbuffer
 */
static _SSD1306_irb_t _SSD1306_irb;

//-------------------------------------------------------------------- [local prototypes]
/**
 * \brief Send a data or command frame with length 1 to the SSD1306.
 *
 * \param type      Payload type, can be #SSD1306_INST_DATA or #SSD1306_INST_CMD see #SSD_ins_t.
 * \param payload   Payload to be send.
 * \return          #RC_SUCCESS if frame was send to the I2C queue \n
                    #RC_ERROR_MEMORY if no memory could be allocated for this operation\n
                    #RC_ERROR_BAD_PARAM if the type is illegal, see #SSD_ins_t.
 * \note this function only can be used if the I2C Task is running.
 */
RC_t _SSD1306_set_instruction(SSD_ins_t type, uint8_t payload);

/**
 * \brief Sets the cursor to a specific position on the OLED
 *
 * \param line      Line/Row in which the cursor is placed, must not exceed #SSD1306_LINES.
 * \param offset    Column in which the cursor is placed, must not exceed #SSD1306_WIDTH.
 * \return          #RC_SUCCESS commands have been put into the queue \n
                    all other results are derived from #_SSD1306_set_instruction.
 * \note this function only can be used if the I2C Task is running.
 */
RC_t _SSD1306_set_cursor(uint8 line, uint8_t offset);

//-------------------------------------------------------------------- [Implementation]

RC_t SSD1306_init(void){
    //result buffer
	RC_t __result;
    
    //line iterator
    uint8_t __line;
    
    //init array length
    uint8_t __init_l=sizeof(init_cmd_array);
    
    //init instruction ringbuffer
    _SSD1306_irb.idx=0;
	
    //Hardware Reset
    //OLED_RES_Write(0);
    //DELAY_MS(100);
	//OLED_RES_Write(1);
	//DELAY_MS(1);
 
    //Send Startup Sequence
    while(__init_l)	{
        
        //send command
		__result=_SSD1306_set_instruction(SSD1306_INST_CMD,init_cmd_array[sizeof(init_cmd_array)-__init_l--]);
        
        //a small delay to decrease ringbuffer size in vI2C
        DELAY_MS(1);
        
        //in case operation failed
        if(__result!=RC_SUCCESS){
            return __result;
        }
	}
    
    //delay to alow OLED startup
    DELAY_MS(1);
    
    // display RAM is undefined after reset, clear it by writing empty lines
    for(__line=0;__line<SSD1306_LINES;__line++){
        __result=SSD1306_write_line(__line,"");
        //a small delay to decrease ringbuffer size in vI2C
        DELAY_MS(1);
        if(__result!=RC_SUCCESS)
            return __result;
    }
    
    //all requests are send to the queue
    return RC_SUCCESS;
}

RC_t _SSD1306_set_instruction(SSD_ins_t type, uint8_t payload){
 
    //result buffer
    RC_t __result;
    
    //pointer to frame buffer
    uint8_t* __p_frame;
    
    //allocate memory for instruction
    __p_frame=&_SSD1306_irb.data[_SSD1306_irb.idx][0];
       
    //set command or data flag
    switch(type){
        case SSD1306_INST_CMD:
            __p_frame[0]=SSD1306_CMD_FLAG;
            break;
            
        case SSD1306_INST_DATA:
            __p_frame[0]=SSD1306_DATA_FLAG;
            break;
            
        //unknown type
        default:
            return RC_ERROR_BAD_PARAM;        
    }

    //copy payload into frame
    __p_frame[1]=payload;
        
    //try to send I2C message
    __result= vI2C_send(SSD1306_I2C_ADR,__p_frame,2,vI2C_FLAG_WRITE,NULL,NULL);  
    if(__result==RC_SUCCESS){
        //increment instruction ringbuffer index
        if(++_SSD1306_irb.idx>=CFG_I2C_QUEUE_L)
            _SSD1306_irb.idx=0;
    }
    else
        LOG_W("SSD1306","failed to send command. Code: 0x%08x",__result);
     
    return __result;
}

RC_t _SSD1306_set_cursor(uint8 line, uint8_t offset){
    
    //result buffer
    RC_t __result;
    
    //check line
    if(!(line<SSD1306_LINES&&offset<SSD1306_WIDTH))
        return RC_ERROR_BAD_PARAM;
    
    //set lower nibble of the column start address
    __result=_SSD1306_set_instruction(SSD1306_INST_CMD,SSD1306_CMDM_CA_L&offset);			
    if(__result!=RC_SUCCESS)return __result;

    //set higher nibble of the column start address
	__result=_SSD1306_set_instruction(SSD1306_INST_CMD,SSD1306_CMDM_CA_H+(offset>>NIBBLE_L));	
    if(__result!=RC_SUCCESS)return __result;
    
    //set row address
	__result=_SSD1306_set_instruction(SSD1306_INST_CMD,SSD1306_CMDM_RA+line);
    if(__result!=RC_SUCCESS)return __result;
    
    //if all commands had been added to the queue, the operation suceeded
    return RC_SUCCESS;
}

RC_t SSD1306_write_line(uint8_t line,char* text){
    
    //output byte iterator
    uint8_t i;
    
    //font byte iterator
    uint8_t f=0;
    
    //pointer to payload buffer    
    static char __OLED_line_buffer[SSD1306_LINES][(SSD1306_WIDTH)+1];
    
    //result buffer
    RC_t __result;
          
    //try to place cursor
    __result=_SSD1306_set_cursor(line,0);
    if(__result!=RC_SUCCESS){
        return __result;
    }
    
    //indicate data start
    __OLED_line_buffer[line][0]=SSD1306_DATA_FLAG;
    
    //fill line
    for(i=1; i<(SSD1306_WIDTH+1);i++){
        //background
        __OLED_line_buffer[line][i]=ascii_table[1][1];
                    
        //padding
        if(i>SSD1306_P_L)
            //text print
            if(*text!=0){
                if(f<SSD1306_F_WIDTH)
                    __OLED_line_buffer[line][i]^=SSD1306_FONT_TBL[(uint8_t)*text][f++];
                else{
                        f=0;
                        text++;
                        if(*text<ASCII_RESERVED_NO_SPACING&&*text!=0)
                            __OLED_line_buffer[line][i]^=SSD1306_FONT_TBL[(uint8_t)*text][f++];
                }              
            }
            
    }            
    
    //try to send frame to queue
    __result=vI2C_send(SSD1306_I2C_ADR,(uint8_t*)__OLED_line_buffer[line],(SSD1306_WIDTH)+1,vI2C_FLAG_WRITE,NULL,NULL);
    
    if(__result!=RC_SUCCESS)
        LOG_W("SSD1306","failed to write line. Code: 0x%08x",__result);
    
    return __result;        
}


/* [] END OF FILE */
