//
// Created by Aspen on 11/7/2020.
//

#ifndef ARDUINO_TEMPERATURE_CONTROLLER_GLOBALS_H
#define ARDUINO_TEMPERATURE_CONTROLLER_GLOBALS_H
#include <math.h>

// SOURCE POWER (Volts)
#define SOURCE_POWER_V 12

/* ***************  FAN CONFIG ******************/

// Minimum operational voltage of the fan before it turns off.
#define FAN0_MIN_VOLTAGE 6
#ifdef FAN0_MIN_VOLTAGE
#define FAN0_MIN_VSCALE_FACTOR SOURCE_POWER_V/FAN0_MIN_VOLTAGE
#endif

// Logarithmic Acceleration Curve. Most aggressive and ensures hardware is kept cool.
#define LOG_FAN0

// Scaling thresholds for Logarithmic curve
#ifdef LOG_FAN0
#define LOG_FAN0_MIN_THRESHOLD 25
#define LOG_FAN0_MAX_THRESHOLD 60
#define LOG_FAN0_B_VALUE pow(LOG_FAN0_MAX_THRESHOLD, 1.0/255)
#endif

// Linear Acceleration Curve. Smoothest mode.
//#define LINEAR_FAN0

// Scaling thresholds for Linear curve
#ifdef LINEAR_FAN0
#define LINEAR_FAN0_MIN_THRESH 25
#define LINEAR_FAN0_MAX_THRESH 60
#endif

// Enable Exponential Acceleration Curve. Least aggressive and quietest mode.
//#define EXP_FAN0

// Scaling thresholds for Exponential curve
#ifdef EXP_FAN0
#define EXP_FAN0_MIN_THRESH 25
#define EXP_FAN0_MAX_THRESH 60
#define EXP_FAN0_BETA 1.025     // input ^ (this number)
#endif

// When enabled this feature will turn the fan off below the specified threshold (temp C)
#define FAN0_DISABLE_THRESHOLD 30

/* *********************** THERMISTOR CONFIGURATION ***************** */
#define THERMISTOR0_NOMINAL 20000
#define THERMISTOR0_NOMINAL_TEMP 25
#define THERMISTOR0_BETA 3950
#define THERMISTOR0_SERIES 20000
#define THERMISTOR0_LINE_VOLTAGE 3.62

#define THERMISTOR1_NOMINAL 20000
#define THERMISTOR1_NOMINAL_TEMP 25
#define THERMISTOR1_BETA 3950
#define THERMISTOR1_SERIES 20000
#define THERMISTOR1_LINE_VOLTAGE 3.62

#define THERMISTOR2_NOMINAL 20000
#define THERMISTOR2_NOMINAL_TEMP 25
#define THERMISTOR2_BETA 3950
#define THERMISTOR2_SERIES 20000
#define THERMISTOR2_LINE_VOLTAGE 3.62

#define THERMISTOR3_NOMINAL 20000
#define THERMISTOR3_NOMINAL_TEMP 25
#define THERMISTOR3_BETA 3950
#define THERMISTOR3_SERIES 20000
#define THERMISTOR3_LINE_VOLTAGE 3.62

#define THERMISTOR4_NOMINAL 20000
#define THERMISTOR4_NOMINAL_TEMP 25
#define THERMISTOR4_BETA 3950
#define THERMISTOR4_SERIES 20000
#define THERMISTOR4_LINE_VOLTAGE 3.62

#define THERMISTOR5_NOMINAL 20000
#define THERMISTOR5_NOMINAL_TEMP 25
#define THERMISTOR5_BETA 3950
#define THERMISTOR5_SERIES 20000
#define THERMISTOR5_LINE_VOLTAGE 3.62


#endif //ARDUINO_TEMPERATURE_CONTROLLER_GLOBALS_H
