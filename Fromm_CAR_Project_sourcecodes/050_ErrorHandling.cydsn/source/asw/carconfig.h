/**
* \file car_cfg.h
* \author P. Fromm
* \date 04.06.21
*
* \brief generic car configuration
*
* detailed description what the file does
*
* \note <notes>
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - 1.0; 04.06.2021; P. Fromm
*            - Initial version
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


 
#ifndef CAR_CFG_H
#define CAR_CFG_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/
#include "global.h"
    
#define CONFIG_REMOTE_BROADCAST '*'
#define CONFIG_REMOTE_CAR_ID 6   
    
#define CONFIG_CAR_MAXSPEED        0.6         /**< \brief in m/s */
#define CONFIG_CAR_MAXROTATION     180         /**< \brief in deg/s */
#define CONFIG_CAR_MAXJOYSTICK     100         /**< \brief in percent */
    

#endif /* STATEMACHINE_CFG_H */
