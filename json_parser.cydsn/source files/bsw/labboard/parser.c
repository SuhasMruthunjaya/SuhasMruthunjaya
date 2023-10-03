/**
* \file parser.h
* \author P. Fromm
* \date 13.11.22
*
* \brief parser based on jsmn.h json parser
*
* detailed description what the file does
*
* \note <notes>
* Programming rules (may be deleted in the final release of the file)
* ===================================================================
*
* 1. Naming conventions:
*    - Prefix of your module in front of every function and static data. 
*    - Scope _ for public and __ for private functions / data / types, e.g. 
*       Public:  void CONTROL_straightPark_Init();
*       Private: static void CONTROL__calcDistance();
*       Public:  typedef enum {RED, GREEN, YELLOW} CONTROL_color_t
*    - Own type definitions e.g. for structs or enums get a postfix _t
*    - #define's and enums are written in CAPITAL letters
* 2. Code structure
*    - Be aware of the scope of your modules and functions. Provide only functions which belong to your module to your files
*    - Prepare your design before starting to code
*    - Implement the simple most solution (Too many if then else nestings are an indicator that you have not properly analysed your task)
*    - Avoid magic numbers, use enums and #define's instead
*    - Make sure, that all error conditions are properly handled
*    - If your module provides data structures, which are required in many other files, it is recommended to place them in a file_type.h file
*	  - If your module contains configurable parts, is is recommended to place these in a file_config.h|.c file
* 3. Data conventions
*    - Minimize the scope of data (and functions)
*    - Global data is not allowed outside of the signal layer (in case a signal layer is part of your design)
*    - All static objects have to be placed in a valid linker sections
*    - Data which is accessed in more than one task has to be volatile and needs to be protected (e.g. by using messages or semaphores)
*    - Do not mix signed and unsigned data in the same operation
* 4. Documentation
*    - Use self explaining function and variable names
*    - Use proper indentation
*    - Provide Javadoc / Doxygen compatible comments in your header file and C-File
*    		- Every  File has to be documented in the header
*			- Every function parameter and return value must be documented, the valid range needs to be specified
*     		- Logical code blocks in the C-File must be commented
*    - For a detailed list of doxygen commands check http://www.stack.nl/~dimitri/doxygen/index.html 
* 5. Qualification
*    - Perform and document design and code reviews for every module
*    - Provide test specifications for every module (focus on error conditions)
*
* Further information:
*    - Check the programming rules defined in the MIMIR project guide
*         - Code structure: https://fromm.eit.h-da.de/intern/mimir/methods/eng_codestructure/method.htm
*         - MISRA for C: https://fromm.eit.h-da.de/intern/mimir/methods/eng_c_rules/method.htm
*         - MISRA for C++: https://fromm.eit.h-da.de/intern/mimir/methods/eng_cpp_rules/method.htm 
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - <version; data of change; author>
*            - <description of the change>
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


 


/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

#include "global.h"
#include "parser.h"
#include "ringbuffer.h"
#include "stdlib.h"
    
//####################### Defines   






/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * Create a parser object
 * \param Parser_t *const me - [OUT] Parser bject pointer
 * \return RC_SUCCESS
 */

RC_t PARSER_init(Parser_t *const me)
{
    jsmn_init(&me->parser);
    for(int i=0; i<PARSERMAXTOKEN; i++)
    {
        me->token[i].end=0;
        me->token[i].size=0;
        me->token[i].start=0;
        me->token[i].type=0;
    }
    
    for(int i=0; i<PARSERSTRINGSIZE; i++)
    {
        me->content[i]=0;
    }
    
    me->nextFreePos=0;
    me->nextToken=0;
    
    return RC_SUCCESS;
}

/**
 * Clear a parser object
 * \param Parser_t *const me - [OUT] Parser object pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_clear(Parser_t *const me)
{
    jsmn_init(&me->parser);
    for(int i=0; i<PARSERMAXTOKEN; i++)
    {
        me->token[i].end=0;
        me->token[i].size=0;
        me->token[i].start=0;
        me->token[i].type=0;
    }
    
    for(int i=0; i<PARSERSTRINGSIZE; i++)
    {
        me->content[i]=0;
    }
    
    me->nextFreePos=0;
    me->nextToken=0;
    
    return RC_SUCCESS;
}


/**
 * Add a char to the buffer
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \param char data - [IN] next char of the json string
 * \return RC_SUCCESS
 */


RC_t PARSER_addChar(Parser_t *const me, char data)
{
    me->content[me->nextFreePos] = data;
    me->nextFreePos++;               
}

/**
 * Add an endl to the buffer
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_addEndl(Parser_t *const me)
{
    me->content[me->token[me->nextToken].end] = '\0';
   
}


/**
 * Perform the parsing and create the token list
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \param char data - [IN] next char of the json string
 * \return RC_SUCCESS
 */
    
char display[sizeof(int)*8+1];



RC_t PARSER_parse(Parser_t *const me)
{
uint8_t parsed_elements;

    parsed_elements = jsmn_parse(&me->parser,me->content, strlen(me->content), 
                    me->token, sizeof(me->token) / sizeof(me->token[0]));
   
}

/**
 * Get the next token of the list
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \param jsmntok_t const* token - [OUT] Next token of the list
 * \return RC_SUCCESS
 */
RC_t PARSER_getNextToken(Parser_t *const me, jsmntok_t *const token)
{   
    me->nextToken++;
    token->start = me->token[me->nextToken].start;
    token->end = me->token[me->nextToken].end;
    token->size = me->token[me->nextToken].size;
    token->type = me->token[me->nextToken].type;
}

/**
 * Reset token iterator
 * \param Parser_t *const me - [IN/OUT] Parser bject pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_resetNextToken(Parser_t *const me)
{
    me->nextToken = 0;
    return RC_SUCCESS;

}


//--------------------- Some debugging aid


/**
 * Print a parser object content
 * \param Parser_t *const me - [OUT] Parser bject pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_dbg_printContent(Parser_t *const me)
{
            UART_LOG_PutString("string:");
            UART_LOG_PutString(me->content);
            UART_LOG_PutString("\r");
            return RC_SUCCESS;

}

/**
 * Print a parser object Tokens
 * \param Parser_t *const me - [OUT] Parser object pointer
 * \return RC_SUCCESS
 */
RC_t PARSER_dbg_printToken(Parser_t *const me)
{   
    char const* enum_names[] = {"JSMN_UNDEFINED", "JSMN_OBJECT","JSMN_ARRAY","JSMN_STRING", "JSMN_PRIMITIVE"};  
    
    int parsed_elements;
        while(me->token[parsed_elements].end!=0)
        {
           parsed_elements++; 
        }
    
    for(int j=0; j<parsed_elements; j++)
            {
            UART_LOG_PutString("tsk_json : Parsed token ");
            itoa(j,display,10);
            UART_LOG_PutString(display);
            UART_LOG_PutString("-");
            UART_LOG_PutString(enum_names[me->token[j].type]);
            UART_LOG_PutString(":");
            for(int i=0; i<(me->token[j].end-me->token[j].start);i++)
            UART_LOG_PutChar(me->content[i + me->token[j].start]);
            UART_LOG_PutString("\r");
            }
}


