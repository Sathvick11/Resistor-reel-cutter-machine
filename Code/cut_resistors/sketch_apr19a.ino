#include "cut_resistor.h"
#include <Stepper.h>
#include "G:\THWS\Semester 6\Engineering Project\Code\Chop\chop\Chop.h"

//Initialization of variables

const int x = 200;
int rotations_per_resistor = -2550;
int number_of_sets = 10; //Taken from the HMI display
int number_of_resistors = 5; // Taken from HMI display

Stepper myStepper(x,2,5);

void cut_resistors()
{
  for(int i = 0; i<number_of_sets; i++)
  {
    myStepper.step(number_of_resistors*rotations_per_resistor);
    delay(5000);
    //Turn on both the servo motors for cutting.
  }
  myStepper.setSpeed(0);
}
/*void setup()
{
myStepper.setSpeed(1000); //1000 - original 
}*/

/*void loop()
{
  //myStepper.step(2400);
  //delay(1000);

}*/