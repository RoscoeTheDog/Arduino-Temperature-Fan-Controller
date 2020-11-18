//
// Created by Aspen on 10/31/2020.
//

#ifndef ARDUINO_TEMPERATURE_CONTROLLER_INTERRUPTS_H
#define ARDUINO_TEMPERATURE_CONTROLLER_INTERRUPTS_H

#include <Arduino.h>
#include <Globals.h>
#include <Interrupts.cpp>

// Timer/Interrupt Configuration
void initializeInterrupts()
{
    // disable all interrupts until needed.
    noInterrupts();


    // ****** INITIALIZE TIMER 1 (8 BIT) **************

    // Clear control registers from any defaults...
    TCCR0A = 0;     // output control register A
    TCCR0B = 0;     // output control register B
    TIMSK0 = 0;     // timer mask register
    TIFR0 = 0;      // timer flag register

    // Set output compare mode (pg 106)
    TCCR0A |= (1 << COM0A1);
    TCCR0A |= (1 << COM0B1);
    // Set waveform generator mode (pg 107)
    TCCR0A |= (1 << WGM01);
    TCCR0A |= (1 << WGM00);
    // Select clock register (pg 109)
    TCCR0B |= (1 << CS00);
    //Enable Compare Match Interrupts (pg 111)
    TIMSK0 |= (1 << OCIE0B);
    TIMSK0 |= (1 << OCIE0A);

    OCR0B = 255;
    OCR0A = 255;

    // ******* INITIALIZE TIMER 2 (16 BIT) **************

    // Clear control registers from any defaults...
//    TCCR1A = 0;     // output control register A
//    TCCR1B = 0;     // output control register B
//    TIMSK1 = 0;     // timer mask register
//    TIFR1 = 0;      // timer flag register

    // Set output compare mode (pg 135)
    TCCR1A |= (1 << COM1A1);
    TCCR1A |= (1 << COM1B1);
    // Set waveform generator mode (pg 136)
    TCCR1A |= (1 << WGM10);
    TCCR1B |= (1 << WGM12);
    // Select clock register (pg 137)
    TCCR1B |= (1 << CS10);
    // Enforce power-reduction register (required for 16-bit modes)
    PRR = (0 << PRTIM1);
    // Enable Compare Match Interrupts (pg 139)
    TIMSK1 |= (1 << OCIE1A);
    TIMSK1 |= (1 << OCIE1B);

    OCR1A = 255;
    OCR1B = 255;

    // ******* INITIALIZE TIMER 3 (8 BIT) **************

    // Clear control registers from any defaults...
    TCCR2A = 0;     // output control register A
    TCCR2B = 0;     // output control register B
    TIMSK2 = 0;     // timer mask register
    TIFR2 = 0;      // timer flag register

    // Set output compare mode (pg 158)
    TCCR2A |= (1 << COM2A1);
    TCCR2A |= (1 << COM2B1);
    // Set waveform generator mode (pg 160)
    TCCR2A |= (1 << WGM21);
    TCCR2A |= (1 << WGM20);
    // select clock register (pg 162)
    TCCR2B |= (1 << CS20);
    // Enable Compare Match Interrupts (pg 163)
    TIMSK2 |= (1 << OCIE2A);
    TIMSK2 |= (1 << OCIE2B);

    OCR2A = 255;
    OCR2B = 255;


    // Re-enable all interrupts
    interrupts();
}

#endif //ARDUINO_TEMPERATURE_CONTROLLER_INTERRUPTS_H
