#ifndef SCREEN_H
#define SCREEN_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

#include "global.h"
#include "position.h"
#include "bat.h"
#include "ball.h"
#include "tft.h"    
    
//####################### Defines/Macros
/** 
 * \brief a brief description of what the define is representing
*
* If needed, a more detailed description can be given below */

  #define SCREEN_HEIGHT 128
  #define SCREEN_WIDTH 160 
   
    

//####################### Enumerations
/**
* \brief Enumerations. Use brief, otherwise the index won't have a brief explanation.
*
* Detailed explaination of the enumeration.
*/


//####################### Structures
/**
* \brief The purpose as well as the members of a structure have to be documented.
*
* Make clear what the structure is used for and what is the purpose of the members.
*/

typedef struct
    {
        BAT_t* m_pBat;
        BALL_t* m_pBall;
        
        //Option 1
        //BACKGROUND_t* m_background;
    } SCREEN_t;

    
    
/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

/**
 * <description>
 */

   

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */



/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

/**
 * <description>
 */


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/


/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
    //Option 1 - Init would also draw the background
 * @return <return description>
 */
RC_t SCREEN_init(SCREEN_t *const me, BAT_t *const pBat, BALL_t *const pBALL);
    
/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t SCREEN_update(SCREEN_t *me);

//Option 2
// We provide extra methods to draw the background
//Pong_init or SOCCER_init have the job to dra the static background
RC_t SCREEN_drawWall(Coordinate_t start, Coordinate_t end, colour c, style s);
RC_t SCREEN_drawNet(Coordinate_t start, Coordinate_t end, colour c, style s);

#endif /* FILE_H */