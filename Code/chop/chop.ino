#include "Chop.h"
#include <Servo.h>
Servo motor1;
Servo motor2;


/*void setup() 
{
//Initalize the positions of the servo motors
  motor1.attach(8);
  motor1.write(55);
  motor2.attach(9);
  motor2.write(175); 
}*/

void chop()
{ 
 motor1.write(115); //initial
 motor2.write(115);

delay(500);

motor1.write(55); //initial
motor2.write(175);


delay(2000);
}

/*void loop() 
{
  chop();

}*/


