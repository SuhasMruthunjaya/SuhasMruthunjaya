/*
 * global.h
 *
 *  Created on: 14.09.2022
 *      Author: Fromm
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_


typedef enum {
	RC_OK,			//! Return ok
	RC_ERROR,		//! Unspecific error
	RC_BADPARAM,	//Wrog parameter value
	RC_EMPTYBUFFER,
	RC_FULLBUFFER,
	RC_NOMEMORY,

}RC_t;

typedef signed char sint8_t;
typedef unsigned char uint8_t;
typedef signed short sint16_t;
typedef unsigned short uint16_t;
typedef signed int sint32_t;
typedef unsigned int uint32_t;






#endif /* GLOBAL_H_ */
