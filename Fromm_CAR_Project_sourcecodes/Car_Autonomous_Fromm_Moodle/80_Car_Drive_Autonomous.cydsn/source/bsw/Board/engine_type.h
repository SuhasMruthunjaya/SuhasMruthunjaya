/**
* \file engine_type.h
* \author P. Fromm
* \date 11.01.20
*
* \brief A simple driver for the JGA25-370 DC engine
*
* The driver creates two PWM signals for the H-bridge (L298) and reads the decoder values
*
* \note <notes>
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - 1.0; 2020.01.11; P. Fromm
*            - Initial release
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


 
#ifndef ENGINE_TYPE_H
#define ENGINE_TYPE_H

#include "global.h"
    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

typedef enum {
    ENG_RR,         /**< \brief engine front right */
    ENG_RL,         /**< \brief engine front left */
    ENG_FR,         /**< \brief engine rear right */
    ENG_FL,         /**< \brief engine rear left */
    ENG_ALL         /**< \brief all engines */
} ENG_id_t;

   

#endif /* ENGINE_H */
