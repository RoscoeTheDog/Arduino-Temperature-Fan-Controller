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

extern volatile float THERMISTOR0_TEMPC;
extern volatile float THERMISTOR1_TEMPC;
extern volatile float THERMISTOR2_TEMPC;
extern volatile float THERMISTOR3_TEMPC;
extern volatile float THERMISTOR4_TEMPC;
extern volatile float THERMISTOR5_TEMPC;

#define THERMISTOR0_NOMINAL 20000
#define THERMISTOR1_NOMINAL 20000
#define THERMISTOR2_NOMINAL 20000
#define THERMISTOR3_NOMINAL 20000
#define THERMISTOR4_NOMINAL 20000
#define THERMISTOR5_NOMINAL 20000

#define THERMISTOR0_LINE_VOLTAGE 3.62
#define THERMISTOR1_LINE_VOLTAGE 3.62
#define THERMISTOR2_LINE_VOLTAGE 3.62
#define THERMISTOR3_LINE_VOLTAGE 3.62
#define THERMISTOR4_LINE_VOLTAGE 3.62
#define THERMISTOR5_LINE_VOLTAGE 3.62

float THERMISTOR0_VO = 0;
float THERMISTOR1_VO = 0;
float THERMISTOR2_VO = 0;
float THERMISTOR3_VO = 0;
float THERMISTOR4_VO = 0;
float THERMISTOR5_VO = 0;

long THERMISTOR0_R1 = 0;
long THERMISTOR1_R1 = 0;
long THERMISTOR2_R1 = 0;
long THERMISTOR3_R1 = 0;
long THERMISTOR4_R1 = 0;
long THERMISTOR5_R1 = 0;

#define THERMISTOR0_SERIES 20000
#define THERMISTOR1_SERIES 20000
#define THERMISTOR2_SERIES 20000
#define THERMISTOR3_SERIES 20000
#define THERMISTOR4_SERIES 20000
#define THERMISTOR5_SERIES 20000

void updateVoltageIn();

void updateR1();

void updateTempC();

float calcTempC(int nominalResistance, int nominalTemperature, long R1, int beta);



#endif //ARDUINO_TEMPERATURE_CONTROLLER_GLOBALS_H
