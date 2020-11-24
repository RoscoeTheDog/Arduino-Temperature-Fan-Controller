//
// Created by Aspen on 11/22/2020.
//

#ifndef ARDUINO_TEMPERATURE_FAN_SPEED_CONTROLLER01_GLOBALS_H
#define ARDUINO_TEMPERATURE_FAN_SPEED_CONTROLLER01_GLOBALS_H

// reserved for the ISR to update their values and read from without performing additional slow analogReads()
extern volatile unsigned long int PIN_A0_READ;
extern volatile unsigned long int PIN_A1_READ;
extern volatile unsigned long int PIN_A2_READ;
extern volatile unsigned long int PIN_A3_READ;
extern volatile unsigned long int PIN_A4_READ;
extern volatile unsigned long int PIN_A5_READ;

extern float THERMISTOR0_VO;
extern unsigned long THERMISTOR0_R1;
extern volatile float THERMISTOR0_TEMPC;
extern volatile float THERMISTOR0_TEMPF;

extern float THERMISTOR1_VO;
extern unsigned long THERMISTOR1_R1;
extern volatile float THERMISTOR1_TEMPC;
extern volatile float THERMISTOR1_TEMPF;

extern float THERMISTOR2_VO;
extern unsigned long THERMISTOR2_R1;
extern volatile float THERMISTOR2_TEMPC;
extern volatile float THERMISTOR2_TEMPF;

extern float THERMISTOR3_VO;
extern unsigned long THERMISTOR3_R1;
extern volatile float THERMISTOR3_TEMPC;
extern volatile float THERMISTOR3_TEMPF;

extern float THERMISTOR4_VO;
extern unsigned long THERMISTOR4_R1;
extern volatile float THERMISTOR4_TEMPC;
extern volatile float THERMISTOR4_TEMPF;

extern float THERMISTOR5_VO;
extern unsigned long THERMISTOR5_R1;
extern volatile float THERMISTOR5_TEMPC;
extern volatile float THERMISTOR5_TEMPF;

#endif //ARDUINO_TEMPERATURE_FAN_SPEED_CONTROLLER01_GLOBALS_H
