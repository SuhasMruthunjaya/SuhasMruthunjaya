/**************************************************
 ** Software Component SWC_Control
 ** autogenerated by H-DA RTE Generator
 **************************************************/

#include "rte.h"
#include "rte_signalpool.h"

#include "cardata.h"
#include "logging.h"
#include "statemachine.h"
#include "statemachine_cfg.h"

#include "swc_control.h"

#include "signal_protocol_type.h"


/*****************************************************************************/
/* State Machine Definition                                                  */
/*****************************************************************************/



/** ---------------------------------- Actions -------------------------------------- **/

/**
 * Will send an acknowledge protocol
 */
static void CONTROL__action_confirmConnect();

/**
 * Will send an acknowledge protocol
 */
static void CONTROL__action_confirmDisconnect();

/**
 * Will send the list of available features
 */
static void CONTROL__action_provideFeatureList();

/**
 * Will start the feature identified by the payload inside the event signal
 */
static void CONTROL__action_activateFeature();

/**
 * Will set the max allowed speed to 0
 */
static void CONTROL__action_stopCar();

/**
 * Driving mode
 */
void CONTROL__Drive();

/**
 * Normal Joystick control
 */
void CONTROL__Joystick();

/**
 * Autonomous driving cleanerbot mode
 */
void CONTROL__CleanerBot();

/** ---------------------------------- Transitions ---------------------------------------- **/

/**  ===== IS_IDLE ====   */
static const STATE_stateInnerTransitionTable_t CONTROL_ISIDLE_Transitions = {
/*    Event                 ToState                 Guard                       Action                       */
    { EV_Connect,           IS_CONNECTED,           0,                          CONTROL__action_confirmConnect}, 
};

/**  ===== IS_CONNECTED ====   */
static const STATE_stateInnerTransitionTable_t CONTROL_ISCONNECTED_Transitions = {
/*    Event                 ToState                 Guard                       Action                       */
    { EV_Reset,             IS_IDLE,                0,                          0}, 
    { EV_Disconnect,        IS_IDLE,                0,                          CONTROL__action_confirmDisconnect}, 
    { EV_RequestFeature,    IS_CONNECTED,           0,                          CONTROL__action_provideFeatureList}, 
    { EV_ActivateFeature,   IS_DRIVING,             0,                          CONTROL__action_activateFeature}, 
};

/**  ===== IS_DRIVING ====   */
static const STATE_stateInnerTransitionTable_t CONTROL_ISDRIVING_Transitions = {
/*    Event                 ToState                 Guard                       Action                       */
    { EV_Joystick,          IS_DRIVING,             0,                          CONTROL__Drive},
    { EV_Reset,             IS_IDLE,                0,                          0}, 
    { EV_Disconnect,        IS_IDLE,                0,                          CONTROL__action_confirmDisconnect}, 
};


static const STATE_stateOuterTransitionTable_t CONTROL_Connection_Transitions = {
/*    fromState         Pointer to table                            Size of table [Elements]    */
    { IS_IDLE,          &CONTROL_ISIDLE_Transitions,                sizeof(CONTROL_ISIDLE_Transitions)/sizeof(STATE_stateInnerTransition_t)    },
    { IS_CONNECTED,     &CONTROL_ISCONNECTED_Transitions,           sizeof(CONTROL_ISCONNECTED_Transitions)/sizeof(STATE_stateInnerTransition_t)     },
    { IS_DRIVING,       &CONTROL_ISDRIVING_Transitions,             sizeof(CONTROL_ISDRIVING_Transitions)/sizeof(STATE_stateInnerTransition_t) },
};
static const uint16_t CONTROL_Connection_Transitions_size = sizeof(CONTROL_Connection_Transitions)/sizeof(STATE_stateOuterTransition_t);

/** ---------------------------------- Action ------------------------------------------- **/

static const STATE_stateActionTable_t CONTROL_Connection_StateActions = {
/*  fromState           Entry                           Exit    */
  { IS_IDLE,            CONTROL__action_stopCar,        0   }
};
static const uint16_t CONTROL_Connection_StateActions_size = sizeof(CONTROL_Connection_StateActions)/sizeof(STATE_stateAction_t);

/** ---------------------------------- Feature table --------------------------------- **/

/**
 * function pointer used for actions
 */
typedef void (*CONTROL_RunPtr_t)();

#define CONTROL_FEATURESTRINGLENGTH 15        //First byte is reserved for index, \0 for termination

typedef struct
{
    CONTROL_RunPtr_t m_run;                                         /**< \brief Pointer to the control loop runnable */
    char             m_description[CONTROL_FEATURESTRINGLENGTH];    /**< \brief string description */
} CONTROL_Feature_t;

static CONTROL_Feature_t CONTROL_FeatureTable[] = {
    /** Runnable                            Description */
    /**                                      123456789012345| */
    { CONTROL__Joystick,                    "Joystick"},
    { CONTROL__CleanerBot,                  "Cleanerbot"},
};
static const uint16_t CONTROL_FeatureTable_size = sizeof(CONTROL_FeatureTable)/sizeof(CONTROL_Feature_t);


/** ---------------------------------- Runnables ---------------------------------------- **/

void CONTROL_init_run()
{
    //Get fromstate and event
    SIGNAL_CARSTATE_data_t state = SIGNAL_CARSTATE_INIT_DATA;
    
    STATE_initState(CONTROL_Connection_StateActions, CONTROL_Connection_StateActions_size, &state);
    
    //Store to-state
    RTE_SIGNAL_CARSTATE_set(&SO_CARSTATE_signal, state);
    
}


void CONTROL_calculateTargetspeed_run()
{
    //Read the joystick data from the RTE
    SIGNAL_JOYSTICK_data_t joystick = RTE_SIGNAL_JOYSTICK_get(&SO_JOYSTICK_signal);
    
    //Calculate the requested target speed
    SIGNAL_SPEED_data_t targetSpeed_requested = SIGNAL_SPEED_INIT_DATA;
    
    //The joystick y-value represents the forward speed
    //The joystick x-value represents the car rotation
    targetSpeed_requested.m_vy = CAR_MAXSPEED * (float)joystick.m_y / CAR_MAXJOYSTICK;
    targetSpeed_requested.m_vphi = CAR_MAXROTATION * (float)joystick.m_x / CAR_MAXJOYSTICK;
    
    //LOG_I("CONTROL_calculateTargetspeed_run","vy = %d vphi = %d", (sint32_t)(targetSpeed_requested.m_vy*100), (sint32_t)(targetSpeed_requested.m_vphi*100));
    
    //Send the target speed requested signal to the limitSpeed runnable
    RTE_SIGNAL_SPEED_set(&SO_TARGETSPEEDREQUESTED_signal, targetSpeed_requested);
}

#define CONTROL_OBSTACLE_SLOW   50
#define CONTROL_OBSTACLE_STOP   25

void CONTROL_limitSpeed_run()
{
    //LOG_I("CONTROL_limitSpeed_run","");
    
    SIGNAL_CARPARAMETERS_data_t param = RTE_SIGNAL_CARPARAMETERS_get(&SO_CARPARAMETER_signal);
    
    SIGNAL_ULTRASONICSENSOR_data_t us_front = RTE_SIGNAL_ULTRASONICSENSOR_get(&SO_USFRONT_signal);
    SIGNAL_ULTRASONICSENSOR_data_t us_rear = RTE_SIGNAL_ULTRASONICSENSOR_get(&SO_USREAR_signal);
    
    LOG_I("CONTROL_limitSpeed_run","Front: %d(%d) Rear: %d(%d)",us_front.m_distance, us_front.m_status,  us_rear.m_distance, us_rear.m_status);
    
    
    //Read the requested speed signal from the RTE
    SIGNAL_SPEED_data_t targetSpeed = RTE_SIGNAL_SPEED_get(&SO_TARGETSPEEDREQUESTED_signal);
    
    //Check for possible obstacles
    if (targetSpeed.m_vy > 0)
    {
        //LOG_I("CONTROL_limitSpeed_run","us_front: %d",us_front.m_distance);
        if (us_front.m_distance < CONTROL_OBSTACLE_STOP)
        {
            targetSpeed.m_vy = 0;
        }
        else if (us_front.m_distance < CONTROL_OBSTACLE_SLOW)
        {
            targetSpeed.m_vy = targetSpeed.m_vy / 2;
        }
        else
        {//Full speed
        }
    }
    else if (targetSpeed.m_vy < 0)
    {
        if (us_rear.m_distance < CONTROL_OBSTACLE_STOP)
        {
            targetSpeed.m_vy = 0;
        }
        else if (us_rear.m_distance < CONTROL_OBSTACLE_SLOW)
        {
            targetSpeed.m_vy = targetSpeed.m_vy / 2;
        }
        else
        {
            //Full speed
        }
       
    }
    //Todo: a bit redundant with the car param signal...
    
    //Check for general speed reduction
    targetSpeed.m_vy = targetSpeed.m_vy * (float)param.m_speedReduction / 100;
    targetSpeed.m_vphi = targetSpeed.m_vphi * (float)param.m_speedReduction / 100;
    
    //Write the limited signal to the RTE
    RTE_SIGNAL_SPEED_set(&SO_TARGETSPEED_signal, targetSpeed);
}



void CONTROL_processCarstate_run()
{
    //Get fromstate and event
    SIGNAL_CARSTATE_data_t state = RTE_SIGNAL_CARSTATE_get(&SO_CARSTATE_signal);
    SIGNAL_EVENT_data_t event = RTE_SIGNAL_EVENT_get(&SO_EVENT_RX_signal);
    
    //Debugging
    //LOG_I("CONTROL_processCarstate_run","Event: %d FromState: %d",event.m_ev,  state);
    
    //Call the state machine
    RC_t result = STATE_processEvent(   CONTROL_Connection_Transitions, CONTROL_Connection_Transitions_size,
                                        CONTROL_Connection_StateActions, CONTROL_Connection_StateActions_size,
                                        event.m_ev, &state);
    
    //Store to-state
    RTE_SIGNAL_CARSTATE_set(&SO_CARSTATE_signal, state);
  
}


/** ---------------------------------- Local Functions ---------------------------------------- **/

/**
 * Will send an acknowledge protocol
 */
static void CONTROL__action_confirmConnect()
{
    SIGNAL_EVENT_data_t ev = SIGNAL_EVENT_INIT_DATA;
    
    ev.m_ev = EV_Connect_ACK;
    
    RTE_SIGNAL_EVENT_set(&SO_EVENT_TX_signal, ev);
}

/**
 * Will send an acknowledge protocol
 */
static void CONTROL__action_confirmDisconnect()
{
    //This protocol is ignored on remote side, may be added later for checking
    SIGNAL_EVENT_data_t ev = SIGNAL_EVENT_INIT_DATA;
    
    ev.m_ev = EV_Disconnect_ACK;
    
    RTE_SIGNAL_EVENT_set(&SO_EVENT_TX_signal, ev);
}

/**
 * Will send the list of available features
 */
static void CONTROL__action_provideFeatureList()
{
    SIGNAL_EVENT_data_t ev = SIGNAL_EVENT_INIT_DATA;
    ev.m_ev = EV_Feature_List;    
    
    uint8_t pos = 0;
    
    //Stringnify the existing features
    for (uint8_t i = 0; i < CONTROL_FeatureTable_size; i++)
    {
        LOG_I("CONTROL__action_provideFeatureList","Processing Feature %d of %d", i, CONTROL_FeatureTable_size);
    
        uint8_t len = strlen(CONTROL_FeatureTable[i].m_description);
        
        //Should not happen, but who knows
        if (len >= CONTROL_FEATURESTRINGLENGTH) len = CONTROL_FEATURESTRINGLENGTH;
        
        //Copy string content
        for (uint8_t l = 0; l < len; l++)
        {
            ev.m_payload[pos++] = CONTROL_FeatureTable[i].m_description[l];
            if (pos >= EVENT_PAYLOADSIZE)
            {
                LOG_E("CONTROL__action_provideFeatureList","payload too large");
                return;
            }

        }
        ev.m_payload[pos++] = '\0'; //String termination
        if (pos >= EVENT_PAYLOADSIZE)
        {
            LOG_E("CONTROL__action_provideFeatureList","payload too large");
            return;
        }
    }

    //Set resulting payload size
    ev.m_lengthPayload = pos;    
    
    //Send data
    RTE_SIGNAL_EVENT_set(&SO_EVENT_TX_signal, ev);
}

/**
 * Will start the feature identified by the payload inside the event signal
 */
static void CONTROL__action_activateFeature()
{
    SIGNAL_CARPARAMETERS_data_t param = RTE_SIGNAL_CARPARAMETERS_get(&SO_CARPARAMETER_signal);
    SIGNAL_EVENT_data_t ev = RTE_SIGNAL_EVENT_get(&SO_EVENT_RX_signal);
    
    param.m_algoIndex = ev.m_payload[0];
    param.m_speedReduction = 100; //Full Speed
    
    LOG_I("CONTROL__action_activateFeature","%d",param.m_algoIndex);
    
    RTE_SIGNAL_CARPARAMETERS_set(&SO_CARPARAMETER_signal, param);
}

/**
 * Will set the max allowed speed to 0
 */
static void CONTROL__action_stopCar()
{
    SIGNAL_CARPARAMETERS_data_t param = RTE_SIGNAL_CARPARAMETERS_get(&SO_CARPARAMETER_signal);
    
    param.m_speedReduction = 0; //Stop
    
    RTE_SIGNAL_CARPARAMETERS_set(&SO_CARPARAMETER_signal, param);
}

/**
 * Driving mode
 */
void CONTROL__Drive()
{
    SIGNAL_CARPARAMETERS_data_t param = RTE_SIGNAL_CARPARAMETERS_get(&SO_CARPARAMETER_signal);
    
    //LOG_I("CONTROL__Drive","%d",param.m_algoIndex);
    
    if (param.m_algoIndex < CONTROL_FeatureTable_size)
    {
        CONTROL_FeatureTable[param.m_algoIndex].m_run();
    }
    
}

/** ---------------------------------- Control Loop Implementations ---------------------------------------- **/

/**
 * Normal Joystick control
 */
void CONTROL__Joystick()
{
    //Read the joystick data from the RTE
    SIGNAL_JOYSTICK_data_t joystick = RTE_SIGNAL_JOYSTICK_get(&SO_JOYSTICK_signal);
    
    //Calculate the requested target speed
    SIGNAL_SPEED_data_t targetSpeed_requested = SIGNAL_SPEED_INIT_DATA;
    
    //The joystick y-value represents the forward speed
    //The joystick x-value represents the car rotation
    targetSpeed_requested.m_vy = CAR_MAXSPEED * (float)joystick.m_y / CAR_MAXJOYSTICK;
    targetSpeed_requested.m_vphi = CAR_MAXROTATION * (float)joystick.m_x / CAR_MAXJOYSTICK;
    
    //LOG_I("CONTROL_calculateTargetspeed_run","vy = %d vphi = %d", (sint32_t)(targetSpeed_requested.m_vy*100), (sint32_t)(targetSpeed_requested.m_vphi*100));
    
    //Send the target speed requested signal to the limitSpeed runnable
    RTE_SIGNAL_SPEED_set(&SO_TARGETSPEEDREQUESTED_signal, targetSpeed_requested);
}


/**
 * Autonomous driving cleanerbot mode
 */
void CONTROL__CleanerBot()
{
    SIGNAL_ULTRASONICSENSOR_data_t us_front = RTE_SIGNAL_ULTRASONICSENSOR_get(&SO_USFRONT_signal);
    SIGNAL_ULTRASONICSENSOR_data_t us_rear = RTE_SIGNAL_ULTRASONICSENSOR_get(&SO_USREAR_signal);
    
    SIGNAL_SPEED_data_t targetSpeed_requested = SIGNAL_SPEED_INIT_DATA;
    
    if (us_front.m_distance > 50)
    {
         targetSpeed_requested.m_vy = CAR_MAXSPEED/2;
         targetSpeed_requested.m_vphi = 0;
    }
    else
    {
        targetSpeed_requested.m_vy = 0;
        targetSpeed_requested.m_vphi = CAR_MAXROTATION ;
    }
    
    LOG_I("CONTROL__CleanerBot","vy = %d vphi = %d", (sint32_t)(targetSpeed_requested.m_vy*100), (sint32_t)(targetSpeed_requested.m_vphi*100));
    
    
    //Send the target speed requested signal to the limitSpeed runnable
    RTE_SIGNAL_SPEED_set(&SO_TARGETSPEEDREQUESTED_signal, targetSpeed_requested);
    
}