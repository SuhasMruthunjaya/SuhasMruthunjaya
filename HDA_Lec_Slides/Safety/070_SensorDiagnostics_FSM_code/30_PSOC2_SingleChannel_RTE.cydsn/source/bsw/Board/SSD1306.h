/**
 * \file 	SSD1306.h
 * \author 	Thomas Barth	- Hochschule Darmstadt thomas.barth@h-da.de
 * \date 	09.07.2017
 * \version 0.3
 *
 * \brief SSD1306 Driver
 *
 * Driver vor OLED Display, driven by an SSD1306.
 *
 * \see https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
 *
 *  Changelog:\n
 *  - 0.3   09.07.2017  Barth
 *            - changed #_SSD1306_set_instruction to static memory
 *            - added #SSD1306_FONT_TBL for easy configuration of the font table
 *  - 0.2   25.06.2017  Barth
 *            - Changed #SSD1306_write_line to static memory
 *            - Adjusted #vI2C_send (no more I2C speed)
 *            - #_SSD1306_set_instruction frees memory if #vI2C_send failes
 *            - logging messages if malloc or #vI2C_send failes
 *  - 0.1   07.11.2016  Barth
 *            - Initial documentation
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

#ifndef SSD1306_H_
#define SSD1306_H_

#include "global.h"
    
#define SSD1306_WIDTH		        128                                 /**< \brief Target display width in pixel*/
#define SSD1306_HEIGHT		        64                                  /**< \brief Target display height in pixel*/
#define SSD1306_LINES	            8                                   /**< \brief Target display number of address row*/
#define SSD1306_I2C_ADR             0b0111100                           /**< \brief SSD1306 I2C address*/
#define SSD1306_F_WIDTH		        5                                   /**< \brief OLED Font width*/
#define SSD1306_CHAR_P_LINE         (SSD1306_WIDTH/(SSD1306_F_WIDTH+1)) /**< \brief maximum number of chars per line (with padding of 1)*/     
#define SSD1306_P_L                 2                                   /**< \brief Padding to the left*/
#define SSD1306_FONT_TBL            ascii_table                         /**< \brief Pointer to font table*/
    
/**
 * \brief Initialize SSD1306 OLED Controller
 *
 * \return          #RC_SUCCESS commands send to low-level driver queue\n
                    #RC_ERROR_MEMORY not sufficent heap-memory for operation */
RC_t SSD1306_init(void);


/**
 * \brief writes a string to a given line on the OLED
 *
 * \param line      Line/Row in which the text shall be written. Must not exceed #SSD1306_LINES.
 * \param text      Text to written into line.
 * \return          #RC_SUCCESS command was passed to low-level driver queue\n
                    #RC_ERROR_MEMORY not sufficent heap-memory for opertion
                    #RC_ERROR_BAD_PARAM invalid \p line 
 * \note this function only can be used if SSD1306_init had been called before.
 */
RC_t SSD1306_write_line(uint8_t line, char* text);


#endif /*SSD1306_H_*/