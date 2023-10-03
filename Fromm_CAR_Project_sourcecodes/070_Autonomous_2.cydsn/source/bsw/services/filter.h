/**
 * \file 	filter.h
 * \author	Peter Fromm 				Hochschule Darmstadt - peter.fromm@h-da.de
 * \date 	08.06.2021
 *
 * \brief 	General purpose ringbuffer mechanism for the use with ERIKA os 
 *
 * \todo This helper is WIP, use with caution 
 *
 * ----- Changelog -----
 *
 *
 * \copyright Copyright ?DateTime inactive during development
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
#ifndef FILTER_H
#define FILTER_H
    
/*=======================[ Includes ]==============================================================*/
    
#include <project.h>
#include "global.h"
    
/*=======================[ Configuration ]===============================================================*/

/**\brief Size of the buffer */
#define FILTER_SIZE     10

/**\brief Datatype to be stored */
typedef sint16_t FILTER_content_t;
    
/**\brief Datatype to store the accumulated data */
typedef sint32_t FILTER_result_t;
    
/*=======================[ Types ]=================================================================*/

/**
 * \brief Filter buffer (FIFO) structure
 */
typedef struct{
    uint16_t            idx_write;                   /**< Write index, points to the next free byte in the buffer */
    uint16_t            filled;                      /**< Number of bytes stored in the buffer*/
    FILTER_content_t    p_payload[FILTER_SIZE];      /**< Filter buffer */
}FILTER_t;
    
/**
 * \brief clears a filter
 * \param   FILTER_t * const me     : [IN/OUT] Filter object to be initialised
 * \return always #RC_SUCCESS
 */
inline RC_t FILTER_Clear(FILTER_t * const me){

    me->idx_write = 0;
    me->filled = 0;
    
    return RC_SUCCESS;
}

/**
 * \brief initializes a filter
 * \param   FILTER_t * const me     : [IN/OUT] Filter object to be initialised
 * \return always #RC_SUCCESS
 */
inline RC_t FILTER_Init(FILTER_t * const me){

    return FILTER_Clear(me);
    
    return RC_SUCCESS;
}

/**
 * \brief get the fillevel of the buffer
 * \param   FILTER_t * const me     : [IN/OUT] Filter object to be initialised
 * \return number of stored elements
 */
inline RC_t FILTER_GetFilllevel(FILTER_t * const me)
{
    return me->filled;
}

/**
 * \brief get the fillevel of the buffer
 * \param   FILTER_t * const me     : [IN/OUT] Filter object to be initialised
 * \return true if buffer is completely filled
 */
inline boolean_t FILTER_IsFilled(FILTER_t * const me)
{
    return me->filled == FILTER_SIZE;
}

/**
 * \brief adds an element to the filter (FIFO). Overrides the oldest element if the buffer is full.
 * \param   FILTER_t * const me     : [IN/OUT] Filter object to be initialised
 * \param   FILTER_content_t data   : [IN]Data object to be added
 * \return always #RC_SUCCESS
 */
inline RC_t FILTER_Add(FILTER_t * const me, FILTER_content_t data)
{
    me->p_payload[me->idx_write++] = data;
    if (me->filled < FILTER_SIZE) me->filled++;
    me->idx_write %= FILTER_SIZE;
    
    return RC_SUCCESS;
}



/**
 * \brief Integrate the content of the filter
 * \param   FILTER_t * const me     : [IN/OUT] Filter object to be initialised
 * \param   FILTER_result_t data    : [OUT] Accumulated result
 * \return #RC_SUCCESS or #RC_ERROR_BUFFER_EMPTY
 */
inline RC_t FILTER_Integrate(FILTER_t * const me, FILTER_result_t *const data)
{
    
    FILTER_result_t result = 0;
    
    if (0 == me->filled) return RC_ERROR_BUFFER_EMTPY;
    
    for (uint16_t i = 0; i < me->filled; i++) result += me->p_payload[i];
    *data = result;
    
    return result;
}


#endif /* FILTER_H*/