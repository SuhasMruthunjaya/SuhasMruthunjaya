/**
* \file dip.h
* \author P. Fromm
* \date 4.4.20
*
* \brief Driver for Watchdog DIP switch
*
*
* \note <notes>
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - <version; data of change; author>
*            - <description of the change>
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
**/


 
#ifndef DIP_H
#define DIP_H
    
#include "global.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

//####################### Defines/Macros

//####################### Enumerations
    
enum eDIPmode {
    DIP_mode_off,       /**< \brief Watchdog is disabled, alive pin is on */
    DIP_mode_alive,     /**< \brief Alive monitoring */
    DIP_mode_window,    /**< \brief Window watchdog monitoring */
    DIP_mode_qa         /**< \brief Question / Answer Monitoring through I2C */
};

typedef enum eDIPmode DIP_mode_t;

//####################### Structures

// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class DIP
{
public:
#endif /* Together */

/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * Read the mode pins (Bit 0 and 1)
 * /param none
 * /return mode enum as specified above
 */
DIP_mode_t DIP_readMode();

/**
 * Read the time pins (Bit 2 and 3)
 * /param none
 * /return 0..3 
 */
uint8_t DIP_readTime();


/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER
};
#endif /* Together */

#endif /* DIP_H */
