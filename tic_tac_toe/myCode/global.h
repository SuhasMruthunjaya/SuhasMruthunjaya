/*
 * global.h
 *
 *  Created on: 14 Nov 2023
 *      Author: suhas
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "iostream"

typedef enum
{
	RC_OK,			//! Return ok
	RC_CONDITIONSATISFIED,
	RC_ERROR,		//! Unspecific error
	RC_BADPARAM,	//Wrog parameter value
	RC_EMPTYBUFFER,
	RC_FULLBUFFER,
	RC_NOMEMORY,

} RC_t;

#endif /* GLOBAL_H_ */

