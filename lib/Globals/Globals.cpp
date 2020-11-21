//
// Created by Aspen on 11/7/2020.
//

#include "Globals.h"

// Values need to be initialized in the cpp file
volatile unsigned long int PIN_A0_READ = 0;
volatile unsigned long int PIN_A1_READ = 0;
volatile unsigned long int PIN_A2_READ = 0;
volatile unsigned long int PIN_A3_READ = 0;
volatile unsigned long int PIN_A4_READ = 0;
volatile unsigned long int PIN_A5_READ = 0;

extern volatile float THERMISTOR0_TEMPC = 0;
extern volatile float THERMISTOR1_TEMPC = 0;
extern volatile float THERMISTOR2_TEMPC = 0;
extern volatile float THERMISTOR3_TEMPC = 0;
extern volatile float THERMISTOR4_TEMPC = 0;
extern volatile float THERMISTOR5_TEMPC = 0;

void updateVoltageIn(){
    THERMISTOR0_VO = (THERMISTOR0_LINE_VOLTAGE / 1023) * PIN_A0_READ;
    THERMISTOR1_VO = (THERMISTOR1_LINE_VOLTAGE / 1023) * PIN_A1_READ;
    THERMISTOR2_VO = (THERMISTOR2_LINE_VOLTAGE / 1023) * PIN_A2_READ;
    THERMISTOR3_VO = (THERMISTOR3_LINE_VOLTAGE / 1023) * PIN_A3_READ;
    THERMISTOR4_VO = (THERMISTOR4_LINE_VOLTAGE / 1023) * PIN_A4_READ;
    THERMISTOR5_VO = (THERMISTOR5_LINE_VOLTAGE / 1023) * PIN_A5_READ;
}

void updateR1(){

    // calculate and store result
//    r1 = ( (lineVoltage * r2) - (r2 * vo)) / vo;

    THERMISTOR0_R1 = (THERMISTOR0_LINE_VOLTAGE * THERMISTOR0_SERIES) - (THERMISTOR0_SERIES * THERMISTOR0_VO) / THERMISTOR0_VO;
    THERMISTOR1_R1 = (THERMISTOR1_LINE_VOLTAGE * THERMISTOR1_SERIES) - (THERMISTOR1_SERIES * THERMISTOR1_VO) / THERMISTOR1_VO;
    THERMISTOR2_R1 = (THERMISTOR2_LINE_VOLTAGE * THERMISTOR2_SERIES) - (THERMISTOR2_SERIES * THERMISTOR2_VO) / THERMISTOR2_VO;
    THERMISTOR3_R1 = (THERMISTOR3_LINE_VOLTAGE * THERMISTOR3_SERIES) - (THERMISTOR3_SERIES * THERMISTOR3_VO) / THERMISTOR3_VO;
    THERMISTOR4_R1 = (THERMISTOR4_LINE_VOLTAGE * THERMISTOR4_SERIES) - (THERMISTOR4_SERIES * THERMISTOR4_VO) / THERMISTOR4_VO;
    THERMISTOR5_R1 = (THERMISTOR5_LINE_VOLTAGE * THERMISTOR5_SERIES) - (THERMISTOR5_SERIES * THERMISTOR5_VO) / THERMISTOR5_VO;

}

void updateTempC(){
    // update the read voltage from thermistor line
    updateVoltageIn();
    // update r1 value from thermistor
    updateR1();

    THERMISTOR0_TEMPC = calcTempC(THERMISTOR0_NOMINAL, 25, THERMISTOR0_R1, 3950);
    THERMISTOR1_TEMPC = calcTempC(THERMISTOR1_NOMINAL, 25, THERMISTOR1_R1, 3950);
    THERMISTOR2_TEMPC = calcTempC(THERMISTOR2_NOMINAL, 25, THERMISTOR2_R1, 3950);
    THERMISTOR3_TEMPC = calcTempC(THERMISTOR3_NOMINAL, 25, THERMISTOR3_R1, 3950);
    THERMISTOR4_TEMPC = calcTempC(THERMISTOR4_NOMINAL, 25, THERMISTOR4_R1, 3950);
    THERMISTOR5_TEMPC = calcTempC(THERMISTOR5_NOMINAL, 25, THERMISTOR5_R1, 3950);
}

float calcTempC(int nominalResistance, int nominalTemperature, long R1, int beta){

    float steinhart;
    steinhart = R1 / nominalResistance;                                // (R/Ro)
    steinhart = log(steinhart);                                         // ln(R/Ro)
    steinhart /= beta;                                         // 1/B * ln(R/Ro)
    steinhart += 1.0 / (nominalTemperature + 273.15); // + (1/To)
    steinhart = 1.0 / steinhart;                                        // Invert
    steinhart -= 273.15;

    return steinhart;
}