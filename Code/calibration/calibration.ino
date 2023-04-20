#include "calibration.h"

int Step_count  = 0;
const int enable_pin = 8;
const int dir_pin = 5;
const int step_pin = 2;

void calibration(int speed)
{
for(Step_count; Step_count< speed; Step_count++)
    // 1350 - one resistor rotation
    // 3200 - half rotation
    //6400 - full rotation
    {
        digitalWrite(enable_pin, HIGH); // enables the stepper motor
        digitalWrite(dir_pin, HIGH);
        digitalWrite(step_pin, LOW);
        delayMicroseconds(500);
        digitalWrite(step_pin, HIGH);
        delayMicroseconds(500);
        Step_count++;
    }
}


/*void loop() 
{
  one_step_at_a_time();
}*/
