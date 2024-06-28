/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief  File containing structure of Position Class
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

#ifndef POSITION_H
#define POSITION_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/
#include "project.h"
#include "global.h"
    
    
//####################### Defines/Macros
/** 
 * \brief a brief description of what the define is representing
*
* If needed, a more detailed description can be given below */

//####################### Enumerations
/**
* \brief Enumerations. Use brief, otherwise the index won't have a brief explanation.
*
* Detailed explaination of the enumeration.

*/

//####################### Structures
/**
* \brief Coordinate x,y needed for Bat,Ball and other logic of the Arcadian games
*  
*/
typedef struct{
    sint16_t X;
    sint16_t Y;
    }Cordinate_t;


/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/



    
    
    
#endif /* FILE_H */