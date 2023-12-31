/**
 * \file 	det.c
 * \author 	Peter Fromm	- Hochschule Darmstadt 
 * \date 	26.11.2016
 * \version 0.1
 *
 * \brief  Logging mechanism
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
/*=======================[ Includes ]===============================================================*/
#include <project.h>
#include "det.h"


/*=======================[ constant data ]===============================================================*/


/*=======================[ variable data ]===============================================================*/

/*=======================[ Function implementation ]=====================================================*/

void DET_Toggle()
{
    static uint8_t toggle = 0;
    
    if (0 == toggle) toggle = 1; else toggle = 0;
    //Pin_Toggle_Write(toggle);
}

/* [] END OF FILE */
