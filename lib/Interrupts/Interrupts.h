//
// Created by Aspen on 10/31/2020.
//

#ifndef ARDUINO_TEMPERATURE_CONTROLLER_INTERRUPTS_H
#define ARDUINO_TEMPERATURE_CONTROLLER_INTERRUPTS_H

#include <Arduino.h>
#include <Globals.h>
#include <Configuration.h>

// Timer/Interrupt Configuration
void initializeInterrupts();

float calcTempC(long nominalResistance, int nominalTemperature, unsigned long R1, int beta);

void updateR1();

void updateVoltageIn();

void updateTempC();

void updateTempF();

#endif //ARDUINO_TEMPERATURE_CONTROLLER_INTERRUPTS_H
