#include "chop.h"
#include <Servo.h>
//Inlcude a function for chopping for better usecase

Servo Servomotor1_left;
Servo Servomotor1_right;
Servo Servomotor2_left;
Servo Servomotor2_right;
void setup()
{
    Servomotor1_left.attach(8);
    Servomotor1_right.attach(9);
    Servomotor2_left.attach(10);
    Servomotor2_right.attach(11);
}

void chop()
{
    for(int steps = 0; steps<120; steps++)
    
    {
        int left_pos_motor_1 = 150 - steps;
        int right_pos_motor_1 = 30  + steps;
        Servomotor1_left.write(left_pos_motor_1);
        Servomotor1_right.write(right_pos_motor_1);
        
        int left_pos_motor_2 = 150 - steps;
        int right_pos_motor_2 = 30 + steps;
        Servomotor2_left.write(left_pos_motor_2);
        Servomotor2_right.write(right_pos_motor_2);
        delay(20);
    }

}