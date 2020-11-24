#include <Thermistor.h>


// TODO: this needs to be worked on. It is not reporting the correct values. Commented out code is older tutorial reference. Will fix later.
void Thermistor::updateTempC()
{
    // update the read voltage from thermistor line
    calcVo();
    // update r1 value from thermistor
    calcR1();

    float steinhart;
    steinhart = r1 / nominalResistance;                                // (R/Ro)
    steinhart = log(steinhart);                                         // ln(R/Ro)
    steinhart /= beta;                                         // 1/B * ln(R/Ro)
    steinhart += 1.0 / (nominalTemperature + 273.15); // + (1/To)
    steinhart = 1.0 / steinhart;                                        // Invert
    steinhart -= 273.15;

    *tempC = steinhart;





//    // convert to Celsius
//    float result = static_cast<float>(
//            ((log(r1 / nominalResistance) / beta) + (1.0 / nominalTemperature + 273.15) / 1.0) - 273.15
//    );
//
//    tempC = result;

    // ***Notes from tutorial for thermistor***


    //  // Read all voltages on the ADC.
    //  for (int i = 0; i < numAnalogPins; ++i){

    //      // SAMPLE SMOOTHING:
    //      float sampleAverage = 0; // Holds the value for the average resistance.

    //      // Resample analog port 'x' times for better accuracy.
    //      for (int j = 0; j < NUM_SAMPLES; ++j) {
    //          sampleAverage += analogRead(pinLogicTable[i]);
    //      }

    //      // Find average from 'x' amount of samples.
    //      sampleAverage /= NUM_SAMPLES;

    //      // If resampling is > 1, it will save the AVERAGE from all samples.
    //      ViTable[i] = sampleAverage;

    //  }

    //  // Find the output Voltage (from the voltage divider circuit).
    //  for (int i = 0; i < numAnalogPins; ++i){
    //      VoTable[i] = (SUPPLY_VCC / 1023) * ViTable[i];
    //  }

    //  // Find the unknown resistance value of the Thermistor, using a Series resistor of known value.
    //  for (int i = 0; i < numAnalogPins; ++i){
    //      R1Table[i] = ( (SUPPLY_VCC * SERIES_RESISTOR) - (SERIES_RESISTOR * VoTable[i]) ) / VoTable[i];
    //  }

    //  // Convert the resistance to Temperature (C).
    //  for (int i = 0; i < numAnalogPins; ++i) {
//          float steinhart;
//          steinhart = R1Table[i] / THERMISTOR_NOMINAL;                                // (R/Ro)
//          steinhart = log(steinhart);                                         // ln(R/Ro)
//          steinhart /= B_COEFFICIENT;                                         // 1/B * ln(R/Ro)
//          steinhart += 1.0 / (TEMPERATURE_NOMINAL + 273.15); // + (1/To)
//          steinhart = 1.0 / steinhart;                                        // Invert
//          steinhart -= 273.15;                                                // convert to C

    //      tempTable[i] = steinhart;
    //  }
}

void Thermistor::calcR1()
{
    // calculate and store result
    r1 = ( (lineVoltage * r2) - (r2 * vo) ) / vo;
}

void Thermistor::calcVo()
{
    // adcValue is pointer to global read variable. Create copy to avoid ISR corrupting it's value mid-calculation.
    unsigned v = *adcValue;

    // calculate thermistor output voltage from divider circuit
    float result = (lineVoltage / 1023) * v;

    vo = result;
}

void Thermistor::printConfig()
{

    for (int j = 0; j < 10; ++j)
    {
        // Check to see if SRAM memory available is less than 60 bytes to load string.
        if (freeMemory() < 12 + 20) // Largest value size is 12 (long double). Prompt size is at least 20 bytes.
        {
            // If it is, flush to the Serial buffer to free up space.
            std::cout.flush();
        }
        else
        {
            switch(j)
            {
                case 0:
//                    std::cout << "Logical Pin Address: " << getLogicalPinAddress() << " ";
//                    break;
//                case 1:
//                    std::cout << "Analog Read: " << getAdcValue() << " ";
//                    break;
//                case 2:
//                    std::cout << "Nominal Resistance: " << getNominalResistance() << " ";
//                    break;
//                case 3:
//                    std::cout << "Beta Value: " << getBeta() << " ";
//                    break;
//                case 4:
//                    std::cout << "Supply Voltage: " << getLineVoltage() << " ";
//                    break;
//                case 5:
//                    std::cout << "Voltage Output: " << getVo() << " ";
//                    break;
//                case 6:
//                    std::cout << "R1: " << getR1() << " ";
//                    break;
//                case 7:
//                    std::cout << "R2: " << getR2() << " ";
//                    break;
                case 8:
                    std::cout << "Temperature (C): " << getTemperatureCelsius() << " ";
                    break;
                case 9:
                    std::cout << "Temperature (F): " << getTemperatureFahrenheit() << " ";
                    break;
            }

        }
        std::cout << '\n';
    }
    std::cout.flush();
}

void Thermistor::updateTempF()
{
    tempF = (*tempC) * 1.8 + 32;
}

