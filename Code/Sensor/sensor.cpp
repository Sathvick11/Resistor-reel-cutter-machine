#include "sensor.h"
#include "G:\THWS\Semester 6\Engineering Project\Code\Move Forward\move_forward.h"

int Sensor_value;
int Resistor_count;

void sensor()
{
    if(Sensor_value<500) // No resistor is detected 
    {
        move_forward();
        delay(20);
    }
    
    if(Sensor_value > 500) // Resistor is detected
    {
        Resistor_count = Resistor_count + 1;
        // Step_count = 0;  // Take the value of Step_count from move_forward.cpp   
        while(Sensor_value>500)
        {
            move_forward();
            Sensor_value = analogRead(); // -----> Mention the analog pin connected to the Arduino
            delay(20);
        }
    }  
}