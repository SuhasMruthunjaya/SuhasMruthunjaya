/**
* \file ex_wdg.h
* \author P. Fromm
* \date 28.6.20
*
* \brief <Symbolic File name>
*
* Driver for the external watchdog
*
* \note <notes>
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - 0.1; 28.6.2020; P. Fromm
*            - First simple alive watchdog
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


 
#ifndef EX_WDG_H
#define EX_WDG_H

#include "global.h"
    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

 enum eExWdg{
    EXWDG_Alive,
    EXWDG_Windows,
    EXWDG_QA,
    
};
typedef enum eExWdg EXWDG_id_t;



// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class EXWDG
{
public:
#endif /* Together */



/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * Watchdog initialisation
 * \param EXWDG_id_t id     - [IN] Type of selected Watchdog Function
 * \return RC_SUCCESS or error code
 */
RC_t EXWDG_Init(EXWDG_id_t id);

/**
 * Watchdog Trigger
 * \return RC_SUCCESS or error code
 */
RC_t EXWDG_Trigger();


/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER



};
#endif /* Together */

#endif /* FILE_H */
