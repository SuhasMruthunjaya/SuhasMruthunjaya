/**
 * \file 	det.h
 * \author 	Peter Fromm	- Hochschule Darmstadt 
 * \date 	27.05.2020
 * \version	1.0
 *
 * \brief Logging and debugging mechanism
 *
 *
 *  Changelog:\n
 *
 * \copyright Copyright ©2018
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

#ifndef DET_H
#define DET_H

/*=======================[ Includes ]==============================================================*/

#include "global.h"


/*=======================[ logging interface ]=================================================================*/


/**
* \brief Toogle pin for timing measurement
*/
void DET_Toggle();


#endif /* DET_H */

/* [] END OF FILE */