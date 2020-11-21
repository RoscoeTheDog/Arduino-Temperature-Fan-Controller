// thermistor-1.ino Simple test program for a thermistor for Adafruit Learning System
// https://learn.adafruit.com/thermistor/using-a-thermistor by Limor Fried, Adafruit Industries
// MIT License - please keep attribution and consider buying parts from Adafruit

#include <pins_arduino.h>
#include <HardwareSerial.h>
#include <USBAPI.h>
#include <Thermistor.h>
#include <ArduinoSTL.h>
#include <Interrupts.h>
#include <Globals.h>

// initialize a List of sensors
std::vector<Thermistor> sensors;

void setup(void)
{
    // Start Arduino Serial Communication
    Serial.begin(115200);

    // Enable all inputs/outputs
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);

    // Initialize a Thermistor Object, passing specifications to the constructor
    Thermistor Thermistor0(&PIN_A0_READ, PIN_A0, &TEMP0_C, 20000, 20000, 3.62);
    Thermistor Thermistor1(&PIN_A1_READ, PIN_A1, &TEMP1_C, 20000, 20000, 5.0);
    Thermistor Thermistor2(&PIN_A2_READ, PIN_A2, &TEMP2_C,20000, 20000, 5.0);
    Thermistor Thermistor3(&PIN_A3_READ, PIN_A3, &TEMP3_C,20000, 20000, 5.0);
    Thermistor Thermistor4(&PIN_A4_READ, PIN_A4, &TEMP4_C,20000, 20000, 5.0);
    Thermistor Thermistor5(&PIN_A5_READ, PIN_A5, &TEMP5_C,20000, 20000, 5.0);

    sensors.push_back(Thermistor0);
    sensors.push_back(Thermistor1);
    sensors.push_back(Thermistor2);
    sensors.push_back(Thermistor3);
    sensors.push_back(Thermistor4);
    sensors.push_back(Thermistor5);

    // Initialize Fast-PWM outputs and interrupt service routines. This checks the ADC each cycle.
    initializeInterrupts();
}

void blockTime(unsigned waitTime) {
    unsigned now = millis();
    while(millis() - now <= waitTime){}
}

void loop(void)
{
//     Get all Thermistors from vector and print each config.
    for (int i = 0; i < sensors.size(); ++i){
        Thermistor * T;
        T = &sensors.at(0); // get reference to object inside.
        T->printConfig();   // print out the Thermistor Statistics.
        std::cout << std::endl; // newline betweeen each probe for readability.
    }
}