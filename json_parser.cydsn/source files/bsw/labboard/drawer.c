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

#include <stdlib.h>
#include "global.h"
#include "ringbuffer.h"
#include "parser.h"
#include "drawer.h"

enum {white,red,black}tft_color;

/**
 * Translates a JSON tag into a command type for the TFT
 * \param Drawer_t *const me            - [OUT] the next command
 * \param Parser_t *const parser        - [IN/OUT] Parser object pointer
 * \return RC_SUCCESS if a command was found, RC_ERROR_BUFFER_EMTPY if parsing has come to an end, other error code as required
 */
RC_t DRAWER_getNextDrawCommand(Drawer_t *const me, Parser_t *const parser)
{
    char display[50];
    char draw_command[50]={};
    char draw_value[50]={};
    char* color[]={"WHITE","BLACK","BLUE","BRED","GRED","GBLUE","RED","MAGENTA","GREEN","CYAN","YELLOW",
                   "BROWN","BRRED","GRAY","DARKBLUE","LIGHTBLUE","GRAYBLUE","LIGHTGREEN","LGRAY",
                    "LGRAYBLUE","LBBLUE"};
    
    TFT_colors_t incoming_color;
   
    jsmntok_t next_command_token;
    jsmntok_t next_value_token;
    PARSER_getNextToken(parser,&next_command_token);
    PARSER_addEndl(parser);
    
    PARSER_getNextToken(parser,&next_value_token);
    PARSER_addEndl(parser);
    
    
    if(next_command_token.type == JSMN_STRING)
      {
         strcat(draw_command,&parser->content[next_command_token.start]);
         if(strcmp(draw_command,"c")==0)
        {
            me->command = DRAWER_CMD_COLOR;
        }
        else if(strcmp(draw_command,"d")==0)
        {
            me->command = DRAWER_CMD_DRAW;
        }
        
      }
    if(next_value_token.type == JSMN_STRING)
    {
         strcat(draw_value,&parser->content[next_value_token.start]);
        
         for(int i=0; i<21; i++)
        {
           if(strcmp(draw_value,color[i])==0)
             
            {
                me->data.color = red;
                break;
            }
        }

    }
    else if(next_value_token.type == JSMN_ARRAY)
    {

        
        for(int i=0; i<4; i++)
        {
           PARSER_getNextToken(parser,&next_value_token);
           PARSER_addEndl(parser);
        
           strcat(draw_value,&parser->content[next_value_token.start]);
           
           me->data.coordinate[i] = atoi(draw_value);
           strcpy(draw_value,"");
           
        }
        
           
    }
    else
       {
            return RC_ERROR_BAD_PARAM;
       }   
    
        
    return RC_SUCCESS;
}