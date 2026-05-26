/**
 * This file contains globals configuration setting to differentiate the 2 PSOCS
 * using the (attention hack) same code base
 **/

#ifndef CONFIG_H
#define CONFIG_H
    
//Change depending on board    
#define PSOC2

#define ERROR_NIBBLE_LOW    1       //Use error pins 1..5
#define ERROR_NIBBLE_HIGH   2       //Use error pins 6..10

#define INACTIVE            0
#define ACTIVE              1

#define WDG_OFF             0
#define WDG_INTERN          1
#define EDG_EXTERN_ALIVE    2
#define EDG_EXTERN_WINDOW   3
#define EDG_EXTERN_QA       4
    
    
/** ---------------------- Configuration for PSOC 2 (left) --------------------------- **/
    
#ifdef PSOC2
    //Actor control
    #define LED             ACTIVE
    #define OLED            ACTIVE
    #define ENGINE          ACTIVE
    
    #define WDG             EDG_EXTERN_ALIVE
    #define WDG_BOOTCHECK   INACTIVE
    
    //Error injection configuration
    #define ERROR ERROR_NIBBLE_HIGH
    
#endif
        
    
#endif