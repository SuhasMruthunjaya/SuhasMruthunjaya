/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */
 
#ifndef GAME_H
#define GAME_H

#include "global.h"
    
typedef enum {
    GAME__ISIDLE,
    //GAME_ISWAITINGRANDOMTIME,
    GAME_ISWAITINGBUTTON,
    }GAME__State_t;  

typedef struct
{
    uint16_t RED;
    uint16_t Green;
    uint16_t Blue;
    uint16_t time;
    
}RG__Glow_t;


//uint8_t i;

void GAME_Play();
static GAME__State_t game = GAME__ISIDLE;
static uint32_t variable_number;
static uint8_t score;
static uint8_t glow_period;
static uint32_t fadar_period;
static uint8_t red;
static uint8_t yellow;
static uint8_t green;
uint16_t Total_Reaction_count;
uint16_t Average_Reaction_count;

RC_t Seven_segment_button(uint32_t variable_number);
RC_t Seven_segment_wait_time(uint32_t variable_number);
void rgb_glower_fun ();
void fadar_fun();
void reaction_game_fun();


void  rgb (RG__Glow_t value);

#endif /* FILE_H */
