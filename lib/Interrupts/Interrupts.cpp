//
// Created by Aspen on 10/31/2020.
//
#include <Arduino.h>
#include <Globals.h>
#include <cmath>

unsigned long int fan0Speed = 0;
unsigned long int fan1Speed = 0;
unsigned long int fan2Speed = 0;
unsigned long int fan3Speed = 0;
unsigned long int fan4Speed = 0;
unsigned long int fan5Speed = 0;
float velocityWeight = 1.25;

// All routine actions. For now, just read the update the sensor data on each compare match.
ISR(TIMER0_COMPA_vect)
{
    PIN_A3_READ = analogRead(A3);
//    fan0Speed = map(fan0Speed, 0, static_cast<long>(1023^2), 0, 255);
//    OCR0A = fan0Speed;
}

ISR(TIMER0_COMPB_vect)
{
    PIN_A4_READ = analogRead(A4);
}

ISR(TIMER1_COMPA_vect)
{
    PIN_A2_READ = analogRead(A2);
}

ISR(TIMER1_COMPB_vect)
{
    PIN_A1_READ = analogRead(A1);
}

ISR(TIMER2_COMPA_vect)
{
    // read/update the value from the ADC
    PIN_A0_READ = analogRead(A0);

    // update temperatures of all probes
    updateTempC();

    // scale the values for PWM output
    fan0Speed = map(static_cast<int>(THERMISTOR0_TEMPC), 20, 60, 255/2, 255);

    // set the frequency of the timer interrupt
    OCR2A = fan0Speed;


//    long maxTemp;
////    maxTemp = map(TEMP0_C, 20, 60, 128, 255);
//
////    // Calculate the value after the set exponential velocity weight is applied
////    fan0Speed = static_cast<long int>(pow(PIN_A0_READ, velocityWeight));
////    // Scale the current weighted value vs max exponential value to an 8 bit PWM output.
////    fan0Speed = map(fan0Speed, 0, static_cast<long int>(pow(1023, velocityWeight)), maxTemp, 255);
//
////    fan0Speed = map(TEMP0_C, 20, 60, pow(PIN_A0_READ, velocityWeight), pow(1023, velocityWeight));
////
////    fan0Speed = map(fan0Speed, pow(PIN_A0_READ, velocityWeight), pow(1023, velocityWeight), 0, 255);
//
//    fan0Speed = map(TEMP0_C, 20, 60, 128, 255);
//
//    OCR2A = fan0Speed;
//
////    // Scale the current temperature reading to the max 8 bit PWM value.
////    fan0Speed = map(TEMP0_C, 20, 60, 255/2, fan0Speed);
//
//
////    // Map the value to a new one within a writable PWM range
////    fan0Speed = map(fan0Speed, 0, static_cast<long int>(pow(1023, velocityWeight)), 255/2, 255);
//
//
//    // Set the value on the Output Compare Register to control the timer's frequency
////    OCR2A = fan0Speed;
}

ISR(TIMER2_COMPB_vect){
    PIN_A5_READ = analogRead(A5);
}