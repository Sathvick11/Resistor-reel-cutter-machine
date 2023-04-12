/*
Code to check if there is any fault with the motor moving. While the stepper motor is moving, the code ensures
that the resistor is also detected while the motor is moving. Else, there is a fault and should stop immediately.
*/


#include "move_forward.h"

int Step_count = 0;
int Max_steps_before_fault = 0;
const int dir_pin; //assign a pin value for dir_pin
const int step_pin;//assign a pin value for step_pin
const int enable_pin; //assign a pin value for enable_pin
const int Max_steps_before_fault = 30; // Can give value of this variable after working on the machine

void move_forward()
{
    if(Step_count < Max_steps_before_fault)
    {
        digitalWrite(enable_pin, LOW); // enables the stepper motor
        digitalWrite(dir_pin, HIGH);
        digitalWrite(step_pin, LOW);
        delayMicroseconds(1000);
        digitalWrite(step_pin, HIGH);
        delayMicroseconds(1000);
        Step_count++;
    }

    else
    {
        //Display error on Nextion display
        digitalWrite(enable_pin, HIGH); // Disables the stepper motor
    }
}

