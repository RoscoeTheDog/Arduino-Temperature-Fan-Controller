//
// Created by Aspen on 10/31/2020.
//
#include <Arduino.h>
#include <Globals.h>

// All routine actions. For now, just read the update the sensor data on each compare match.
ISR(TIMER0_COMPA_vect)
{
    PIN_A3_READ = analogRead(A3);
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

ISR(TIMER2_COMPA_vect){
    PIN_A0_READ = analogRead(A0);
}

ISR(TIMER2_COMPB_vect){
    PIN_A5_READ = analogRead(A5);
}