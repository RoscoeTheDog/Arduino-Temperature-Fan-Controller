//
// Created by Aspen on 11/7/2020.
//

#ifndef ARDUINO_TEMPERATURE_CONTROLLER_GLOBALS_H
#define ARDUINO_TEMPERATURE_CONTROLLER_GLOBALS_H
#include <ArduinoSTL.h>

// These will run in a ISR periodically to update their values.
extern volatile unsigned long int PIN_A0_READ;
extern volatile unsigned long int PIN_A1_READ;
extern volatile unsigned long int PIN_A2_READ;
extern volatile unsigned long int PIN_A3_READ;
extern volatile unsigned long int PIN_A4_READ;
extern volatile unsigned long int PIN_A5_READ;

extern volatile float TEMP0_C;
extern volatile float TEMP1_C;
extern volatile float TEMP2_C;
extern volatile float TEMP3_C;
extern volatile float TEMP4_C;
extern volatile float TEMP5_C;


#endif //ARDUINO_TEMPERATURE_CONTROLLER_GLOBALS_H
