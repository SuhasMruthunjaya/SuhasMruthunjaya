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
    /*For more information, refer to the Writing Code topic in the PSoC Creator Help.*/

    extern void vI2C_ISR();
    #define I2C_ISR_EXIT_CALLBACK
    #define I2C_ISR_ExitCallback()     vI2C_ISR();
    
#endif /* CYAPICALLBACKS_H */   
/* [] */
