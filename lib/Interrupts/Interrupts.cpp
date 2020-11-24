//
// Created by Aspen on 10/31/2020.
//
#include <Interrupts.h>

unsigned long int fan0 = 0;
unsigned long int fan1Speed = 0;
unsigned long int fan2Speed = 0;
unsigned long int fan3Speed = 0;
unsigned long int fan4Speed = 0;
unsigned long int fan5Speed = 0;

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
    // Enable Compare Match Interrupts (pg 111)
//    TIMSK0 |= (1 << OCIE0B);
//    TIMSK0 |= (1 << OCIE0A);

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
//    TIMSK2 |= (1 << OCIE2B);

    OCR2A = 255;
    OCR2B = 255;


    // Re-enable all interrupts
    interrupts();
}


// All routine actions. For now, just read the update the sensor data on each compare match.
ISR(TIMER0_COMPA_vect)
{
    PIN_A3_READ = analogRead(A3);
//    fan0 = map(fan0, 0, static_cast<long>(1023^2), 0, 255);
//    OCR0A = fan0;
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
    // update the value from the ADC
    PIN_A0_READ = analogRead(A0);

    // update temperatures of all probes
    updateTempC();
    updateTempF();

    // determine the acceleration mode (set via configuration.h)
#ifdef LOG_FAN0
    fan0 = map(pow(THERMISTOR0_TEMPC, LOG_FAN0_B_VALUE), LOG_FAN0_MIN_THRESHOLD, LOG_FAN0_MAX_THRESHOLD, 255/FAN0_MIN_VSCALE_FACTOR, 255);
#endif

#ifdef LINEAR_FAN0
    fan0 = map(THERMISTOR_TEMPC, LINEAR_FAN0_MIN_THRESH, LINEAR_FAN0_MAX_THRESH, 255/FAN0_MIN_VSCALE_FACTOR, 255)
#endif

#ifdef EXP_FAN0
    // Scale the input temperature to be a usable PWM output within given thresholds
    int temp = map(THERMISTOR0_TEMPC, EXP_FAN0_MIN_THRESHOLD, EXP_FAN0_MAX_THRESHOLD, 255/FAN0_MIN_VSCALE_FACTOR, 255);

    // value after beta (weight) factor is applied
    fan0 = static_cast<long int>(pow(PIN_A0_READ, EXP_FAN0_BETA));

    // Scale adc input beta to max beta range of PWM output.
    fan0 = map(fan0, 0, static_cast<long int>(pow(1023, EXP_FAN0_BETA)), temp, 255);
#endif

    // Enforce a limit to max frequency of timer
    if (fan0 > 255)
        fan0 = 255;

    // turn off fan below temperature threshold
#ifdef FAN0_DISABLE_THRESHOLD
    if (THERMISTOR0_TEMPC < FAN0_DISABLE_THRESHOLD)
        fan0 = 0;
#endif

    // set the frequency of the timer interrupt
    OCR2A = fan0;


//
//    fan0 = map(TEMP0_C, 20, 60, 128, 255);
//
//    OCR2A = fan0;
//
////    // Scale the current temperature reading to the max 8 bit PWM value.
////    fan0 = map(TEMP0_C, 20, 60, 255/2, fan0);
//
//
////    // Map the value to a new one within a writable PWM range
////    fan0 = map(fan0, 0, static_cast<long int>(pow(1023, velocityWeight)), 255/2, 255);
//
//
//    // Set the value on the Output Compare Register to control the timer's frequency
////    OCR2A = fan0;
}

ISR(TIMER2_COMPB_vect)
{
    PIN_A5_READ = analogRead(A5);
}

void updateVoltageIn()
{
    THERMISTOR0_VO = THERMISTOR0_LINE_VOLTAGE / 1023 * PIN_A0_READ;
//    THERMISTOR1_VO = static_cast<float>((THERMISTOR1_LINE_VOLTAGE / 1023) * PIN_A1_READ);
//    THERMISTOR2_VO = static_cast<float>((THERMISTOR2_LINE_VOLTAGE / 1023) * PIN_A2_READ);
//    THERMISTOR3_VO = static_cast<float>((THERMISTOR3_LINE_VOLTAGE / 1023) * PIN_A3_READ);
//    THERMISTOR4_VO = static_cast<float>((THERMISTOR4_LINE_VOLTAGE / 1023) * PIN_A4_READ);
//    THERMISTOR5_VO = static_cast<float>((THERMISTOR5_LINE_VOLTAGE / 1023) * PIN_A5_READ);
}

void updateR1()
{
    // Calculate and update the Thermistors resistance...

    /*
     *      1) ADC = V1 * (R2 / R1 + R2)    // Isolate R1
     *      2) (R1 + R2) * ADC  = V1 * R2   // Multiply the denominator
     *      3) (R1 * ADC) + (R2 * ADC) = V1 * R2    // distribute terms
     *      4) (R1 * ADC) = (V1 * R2) - (R2 * ADC)  // isolate R1 variable on one side
     *      5) (R1) = (V1 * R2) - (R2 * ADC) / ADC  // Simplify
     */

    THERMISTOR0_R1 = ((THERMISTOR0_LINE_VOLTAGE * THERMISTOR0_SERIES) - (THERMISTOR0_SERIES * THERMISTOR0_VO)) / THERMISTOR0_VO;

//    THERMISTOR1_R1 = static_cast<long>(
//            ((THERMISTOR1_LINE_VOLTAGE * THERMISTOR1_SERIES) -
//             (THERMISTOR1_SERIES * THERMISTOR1_VO)) /
//            THERMISTOR1_VO
//    );
//
//    THERMISTOR2_R1 = static_cast<long>(
//            ((THERMISTOR2_LINE_VOLTAGE * THERMISTOR2_SERIES) -
//             (THERMISTOR2_SERIES * THERMISTOR2_VO)) /
//            THERMISTOR2_VO
//    );
//
//    THERMISTOR3_R1 = static_cast<long>(
//            ((THERMISTOR3_LINE_VOLTAGE * THERMISTOR3_SERIES) -
//             (THERMISTOR3_SERIES * THERMISTOR3_VO)) /
//            THERMISTOR3_VO
//    );
//
//    THERMISTOR4_R1 = static_cast<long>(
//            ((THERMISTOR4_LINE_VOLTAGE * THERMISTOR4_SERIES) -
//             (THERMISTOR4_SERIES * THERMISTOR4_VO)) /
//            THERMISTOR4_VO
//    );
//
//    THERMISTOR5_R1 = static_cast<long>(
//            ((THERMISTOR5_LINE_VOLTAGE * THERMISTOR5_SERIES) -
//             (THERMISTOR5_SERIES * THERMISTOR5_VO)) /
//            THERMISTOR5_VO
//    );
}

float calcTempC(long nominalResistance, int nominalTemperature, unsigned long R1, int beta)
{

    float steinhart;
    steinhart = static_cast<float>(R1) / static_cast<float>(nominalResistance);                                // (R/Ro)
    steinhart = log(steinhart);                                         // ln(R/Ro)
    steinhart /= beta;                                         // 1/B * ln(R/Ro)
    steinhart += 1.0 / (nominalTemperature + 273.15); // + (1/To)
    steinhart = 1.0 / steinhart;                                        // Invert
    steinhart -= 273.15;

    return steinhart;
}

void updateTempC()
{
    // Update the voltage from ADC
    updateVoltageIn();
    // Update R1 value of thermistor
    updateR1();
    // Calc and update Temperatures
    THERMISTOR0_TEMPC = calcTempC(THERMISTOR0_NOMINAL, THERMISTOR0_NOMINAL_TEMP, THERMISTOR0_R1, THERMISTOR0_BETA);
//    THERMISTOR1_TEMPC = calcTempC(THERMISTOR1_NOMINAL, THERMISTOR1_NOMINAL_TEMP, THERMISTOR1_R1, THERMISTOR1_BETA);
//    THERMISTOR2_TEMPC = calcTempC(THERMISTOR2_NOMINAL, THERMISTOR2_NOMINAL_TEMP, THERMISTOR2_R1, THERMISTOR2_BETA);
//    THERMISTOR3_TEMPC = calcTempC(THERMISTOR3_NOMINAL, THERMISTOR3_NOMINAL_TEMP, THERMISTOR3_R1, THERMISTOR3_BETA);
//    THERMISTOR4_TEMPC = calcTempC(THERMISTOR4_NOMINAL, THERMISTOR4_NOMINAL_TEMP, THERMISTOR4_R1, THERMISTOR4_BETA);
//    THERMISTOR5_TEMPC = calcTempC(THERMISTOR5_NOMINAL, THERMISTOR5_NOMINAL_TEMP, THERMISTOR5_R1, THERMISTOR5_BETA);
}

void updateTempF(){
    THERMISTOR0_TEMPF = THERMISTOR0_TEMPC * 1.8 + 32;
    THERMISTOR1_TEMPF = THERMISTOR1_TEMPC * 1.8 + 32;
    THERMISTOR2_TEMPF = THERMISTOR2_TEMPC * 1.8 + 32;
    THERMISTOR3_TEMPF = THERMISTOR3_TEMPC * 1.8 + 32;
    THERMISTOR4_TEMPF = THERMISTOR4_TEMPC * 1.8 + 32;
    THERMISTOR5_TEMPF = THERMISTOR5_TEMPC * 1.8 + 32;
}