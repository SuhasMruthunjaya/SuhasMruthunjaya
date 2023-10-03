/**
* \file engine_cfg.c
* \author P. Fromm
* \date 11.1.20
*
* \brief Engine Driver Configuration for 4 engines
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
*/


#include "engine_cfg.h" 

/*****************************************************
 ** Car Configuration
 ****************************************************/

const ENG_orientation_t ENG_orientation[ENG_ALL] = {
    { ENG_RR,   -1,     -1},    //PWM_Rear_2
    { ENG_RL,    1,      1},    //PWM_Rear_1
    { ENG_FR,    1,     -1},    //PWM_Front_2
    { ENG_FL,   -1,      1},    //PWM_Front_1
};

/**
 * Get engine orientation
 * \param ENG_id_t id       : IN - The engine identifier 
 * \return -1 or 1, 0 in case of error
 */
sint8_t ENG_getEngineOrientation(ENG_id_t id)
{
    if (ENG_orientation[id].m_id == id)
    {
        return ENG_orientation[id].m_dir_eng;
    }
    else
    {
        return 0;
    }
}


/**
 * Get decoder orientation
 * \param ENG_id_t id       : IN - The engine identifier 
 * \return -1 or 1, 0 in case of error
 */
sint8_t ENG_getDecoderOrientation(ENG_id_t id)
{
    if (ENG_orientation[id].m_id == id)
    {
        return ENG_orientation[id].m_dir_dec;
    }
    else
    {
        return 0;
    }
}

/*****************************************************
 ** Open Loop Calibration Curve
 ****************************************************/




const ENG_calibration_t ENG_cal_forward[] = {
  { 0 , 0 }, 
  { 5 , 2800 }, 
  { 10 , 2800 }, 
  { 15 , 2800 }, 
  { 20 , 2800 }, 
  { 25 , 2800 }, 
  { 30 , 2800 }, 
  { 35 , 2800 }, 
  { 40 , 2800 }, 
  { 45 , 2800 }, 
  { 50 , 2800 }, 
  { 55 , 2800 }, 
  { 60 , 2800 }, 
  { 65 , 2800 }, 
  { 70 , 2800 }, 
  { 75 , 2800 }, 
  { 80 , 3000 }, 
  { 85 , 3100 }, 
  { 90 , 3200 }, 
  { 95 , 3250 }, 
  { 100 , 3350 }, 
  { 105 , 3500 }, 
  { 110 , 3600 }, 
  { 115 , 3700 }, 
  { 120 , 3850 }, 
  { 125 , 4000 }, 
  { 130 , 4100 }, 
  { 135 , 4200 }, 
  { 140 , 4350 }, 
  { 145 , 4550 }, 
  { 150 , 4700 }, 
  { 155 , 4850 }, 
  { 160 , 5050 }, 
  { 165 , 5300 }, 
  { 170 , 5450 }, 
  { 175 , 5700 }, 
  { 180 , 5850 }, 
  { 185 , 6250 }, 
  { 190 , 6500 }, 
  { 195 , 6850 }, 
  { 200 , 7150 }, 
  { 205 , 7750 }, 
  { 210 , 8000 }, 
  { 215 , 8500 }, 
  { 220 , 9000 }, 
  { 225 , 9650 }, 
  { 230 , 9850 }, 
  { 235 , 9950 }, 
};

const uint16_t ENG_cal_forward_size = sizeof(ENG_cal_forward)/sizeof(ENG_calibration_t);


const ENG_calibration_t ENG_cal_backward[] = {
  { 0 , 0 }, 
  { -5 , -2700 }, 
  { -10 , -2700 }, 
  { -15 , -2700 }, 
  { -20 , -2700 }, 
  { -25 , -2700 }, 
  { -30 , -2700 }, 
  { -35 , -2700 }, 
  { -40 , -2700 }, 
  { -45 , -2700 }, 
  { -50 , -2700 }, 
  { -55 , -2700 }, 
  { -60 , -2700 }, 
  { -65 , -2700 }, 
  { -70 , -2700 }, 
  { -75 , -2850 }, 
  { -80 , -3000 }, 
  { -85 , -3150 }, 
  { -90 , -3250 }, 
  { -95 , -3350 }, 
  { -100 , -3400 }, 
  { -105 , -3550 }, 
  { -110 , -3650 }, 
  { -115 , -3800 }, 
  { -120 , -3900 }, 
  { -125 , -4100 }, 
  { -130 , -4200 }, 
  { -135 , -4350 }, 
  { -140 , -4500 }, 
  { -145 , -4750 }, 
  { -150 , -4900 }, 
  { -155 , -5050 }, 
  { -160 , -5300 }, 
  { -165 , -5550 }, 
  { -170 , -5750 }, 
  { -175 , -6000 }, 
  { -180 , -6300 }, 
  { -185 , -6700 }, 
  { -190 , -7000 }, 
  { -195 , -7350 }, 
  { -200 , -7750 }, 
  { -205 , -8400 }, 
  { -210 , -8900 }, 
  { -215 , -9300 }, 
  { -220 , -9750 }, 
  { -225 , -9900 }, 
};

const uint16_t ENG_cal_backward_size = sizeof(ENG_cal_backward)/sizeof(ENG_calibration_t);
