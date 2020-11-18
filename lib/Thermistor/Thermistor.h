//
// Created by Aspen on 10/19/2020.
//

#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <Arduino.h>
#include <ArduinoSTL.h>
#include <Globals.h>
#include <MemoryFree.h>

class Thermistor
{
private:
    volatile unsigned int *adcValue = nullptr;
    const int logicalPinAddress;
    const long nominalResistance; // known nominal rating of thermistor
    const int nominalTemperature; // temperature at which known resistance for thermistor is rated (default 25C if not known)
    const int beta;
    const float lineVoltage;    // Voltage used on the thermistor circuit
    float vo;   // incoming Voltage on the ADC from divider circuit
    float r1;   // current resistance of thermistor (calculated from the voltage divider)
    const long int r2;   // R2 is the series resistor in the divider circuit (required for calculating R1)
    float tempC;
    float tempF;

private:
    void updateTempC();

    void updateTempF();

    void calcVo();

    void calcR1();

public:

    Thermistor(volatile unsigned int *analogRead, int pinAddress, long int nominalResistance, long int R2, float lineVoltage,
               int beta = 3950, int nominalTemperature = 25) :
            adcValue(analogRead), logicalPinAddress(pinAddress), nominalResistance(nominalResistance),
            lineVoltage(lineVoltage), r2(R2), beta(beta), nominalTemperature(nominalTemperature){};

    volatile unsigned int getAdcValue() { return *adcValue; }

    int getLogicalPinAddress() const { return logicalPinAddress; }

    long int getNominalResistance() const { return nominalResistance; }

    int getBeta() const { return beta; }

    float getLineVoltage() const { return lineVoltage; }

    float getVo() { calcVo(); return vo;};

    float getR1() { calcR1(); return r1;};

    float getR2() const { return r2; }

    float getTemperatureCelsius() { updateTempC(); return tempC; }

    float getTemperatureFahrenheit() { updateTempF(); return tempF; }

    void printConfig();
};


#endif //ARDUINO_TEMPERATURE_CONTROLLER_THERMISTOR
