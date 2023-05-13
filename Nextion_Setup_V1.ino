#include <Nextion.h>
#include <SoftwareSerial.h>
#include <Stepper.h>
#include <Servo.h>

//SoftwareSerial Serial(12, 13);
NexProgressBar pb = NexProgressBar(3,6,"j0");
int prog_quant = 0;

int stop = 0;
int b1_done = 0;
int b2_done = 0;

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

void chop_belt1()
{ 
    motor1.write(120); //initial
    motor2.write(0);

    delay(500);

    motor1.write(35); //initial
    motor2.write(90);

    delay(500);

}

void chop_belt2()
{ 
    motor3.write(80); //initial
    motor4.write(90);

    delay(500);

    motor3.write(150); //initial
    motor4.write(0);

    delay(500);

}

const int enable_pin = 8;
const int dir_pin = 5;
const int step_pin = 2;
const int dir_pin_2 = 6;
const int step_pin_2 = 3;

void calibration_forward_1(int speed)
{
  int Step_count  = 0;
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
    }
}

void calibration_back_2(int speed)
{
  int Step_count  = 0;
  for(Step_count; Step_count< speed; Step_count++)
    // 1350 - one resistor rotation
    // 3200 - half rotation
    //6400 - full rotation
    {
        digitalWrite(enable_pin, HIGH); // enables the stepper motor
        digitalWrite(dir_pin_2, HIGH);
        digitalWrite(step_pin_2, LOW);
        delayMicroseconds(500);
        digitalWrite(step_pin_2, HIGH);
        delayMicroseconds(500);
    }
}

void calibration_back_1(int speed)
{
  int Step_count  = speed;
  for(Step_count; Step_count> 0; Step_count--)
    // 1350 - one resistor rotation
    // 3200 - half rotation
    //6400 - full rotation
    {
        digitalWrite(enable_pin, HIGH); // enables the stepper motor
        digitalWrite(dir_pin, LOW);
        digitalWrite(step_pin, LOW);
        delayMicroseconds(500);
        digitalWrite(step_pin, HIGH);
        delayMicroseconds(500);
    }
}

void calibration_forward_2(int speed)
{
  int Step_count  = speed;
  for(Step_count; Step_count> 0; Step_count--)
    // 1350 - one resistor rotation
    // 3200 - half rotation
    //6400 - full rotation
    {
        digitalWrite(enable_pin, HIGH); // enables the stepper motor
        digitalWrite(dir_pin_2, LOW);
        digitalWrite(step_pin_2, LOW);
        delayMicroseconds(500);
        digitalWrite(step_pin_2, HIGH);
        delayMicroseconds(500);
    }
}


//Page 0 : Home
NexDSButton bt1 = NexDSButton(0,6,"bt0");//Belt 1 ON/OFF
NexDSButton bt2 = NexDSButton(0,11,"bt0");//Belt 2 ON/OFF
int bt1s = 1;//Belt 1 On
int bt2s = 1;//Belt 2 On

//Page 1 : Numberpad no data transfer from this page to arduino
//Page 2 : Setup/Calibration
NexDSButton blt = NexDSButton(2,15,"bt0");//belt 1/belt 2 for calibration
int which_belt = 1;//2 for belt 2 

NexPicture forward = NexPicture(2,2,"p1");// Forward arrow (DOWN)
NexPicture back = NexPicture(2,6,"p2");// Forward arrow (DOWN)

NexButton start = NexButton(2,5,"b0");//Start cutting process
int start_cutting = 0;// Start set to off 0
NexVariable sets1 = NexVariable(2,7,"va0");
NexVariable comps1 = NexVariable(2,9,"va2");
NexVariable sets2 = NexVariable(2,8,"va1");
NexVariable comps2 = NexVariable(2,10,"va3");

int b1_sets = 0;
int b1_comps = 0;
int b2_sets = 0;
int b2_comps = 0;
uint32_t number = 0;//number pointer to get values from nextion

NexButton fast = NexButton(2,12,"b2");//Belt config speed: Fast
NexButton medium = NexButton(2,13,"b3");//Belt config speed: Fast
NexButton slow = NexButton(2,14,"b4");//Belt config speed: Fast
int speed = 2550;//2550-slow 3200-medium 6400-fast

//page 3: Final, after process has been started

//NexNumber proc_done = NexNumber(3,5,"n0");//For page transition after cutting process is done, should be set to more than 0 if done

NexButton cdone = NexButton(3,7,"b1");
//page 4: After cutting done

//NexButton done_home = NexButton(4,3,"b0");//to reset values on arduino

//page 5: Stop page, to confirm stop

NexButton stop_yes = NexButton(5,3,"b0");//Stop has been confirmed

//Register a button object to the touch event list
NexTouch *nex_listen_list[] = {
  &bt1,
  &bt2,
  &forward,
  &back,
  &start,
  &fast,
  &medium,
  &slow,
  &stop_yes, 
  &blt,
  NULL
};

void bltPopCallBack(void *ptr){
  if(which_belt == 1){
  which_belt=2;
  Serial.println("Belt 2");}
  else{
    which_belt=1;
    Serial.println("Belt 1");
  }
}
//belt 1 ON/OFF
void bt1PopCallBack(void *ptr){
  if(bt1s == 1){
      bt1s = 0;
      Serial.println("Belt 1:OFF");
  }
  else{
    bt1s = 1;
    Serial.println("Belt 1:ON");
  }
}

//belt 1 ON/OFF
void bt2PopCallBack(void *ptr){
  if(bt2s == 1){
      bt2s = 0;
      Serial.println("Belt 2:OFF");
  }
  else{
    bt2s = 1;
    Serial.println("Belt 2:ON");
  }
}

//slow speed
void slowPopCallBack(void *ptr){
  speed = 675;
  Serial.println("Speed:Slow");
  //done_page_trans();
}

//medium speed
void mediumPopCallBack(void *ptr){
  speed = 3200;
  Serial.println("Speed:Medium");
}

//fast speed
void fastPopCallBack(void *ptr){
  speed = 6400;
  Serial.println("Speed:Fast");
}

//Start
void startPopCallBack(void *ptr){
  start_cutting = 1;
  stop = 0;
  Serial.println("Cutting Start");

  sets1.getValue(&number);
  Serial.println();
  b1_sets = number;
  Serial.print("Sets1:");
  Serial.println(b1_sets);
  Serial.println();

  comps1.getValue(&number);
  Serial.println();
  b2_sets = number;
  Serial.print("Sets2:");
  Serial.println(b2_sets);
  Serial.println();

  sets2.getValue(&number);
  Serial.println();
  b1_comps = number;
  Serial.print("Comps1:");
  Serial.println(b1_comps);
  Serial.println();

  comps2.getValue(&number);
  Serial.println();
  b2_comps = number;
  Serial.print("Comps2:");
  Serial.println(b2_comps);

  if(stop == 0){
    if(bt1s == 1){  
  cut_resistors_1(b1_sets,b1_comps);}
  b1_done = 1;
  pb.setValue(50);
  delay(200);
  if(bt2s == 1){
  cut_resistors_2(b2_sets,b2_comps);}
  b2_done = 1;
  pb.setValue(100);
  //cdone.Set_background_color_bco(1024);
  }
}

void forwardPopCallBack(void *ptr){
  Serial.println("Forward");
  if(which_belt == 1){
  calibration_forward_1(speed);
  }
  else{
  calibration_forward_2(speed);  
  }
}

void backPopCallBack(void *ptr){
  Serial.println("Back");
  if(which_belt == 1){
  calibration_back_1(speed);
  }
  else{
    calibration_back_2(speed);
  }
}

void stop_yesPopCallBack(void *ptr){
  stop = 1;
  Serial.println("STOP!!!!");
  which_belt = 1;
  b1_sets = 0;
  b1_comps = 0;
  b2_sets = 0;
  b2_comps = 0;
  b1_done = 0;
  b2_done = 0;
  pb.setValue(0);
}

void done_page_trans()
{
  Serial.print("page 4");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

const int x = 200;
int rotations_per_resistor = 2550;

Stepper myStepper(x,2,5);
Stepper myStepper1(x,3,6);

void cut_resistors_1(int number_of_sets, int number_of_resistors){
  myStepper.setSpeed(1000);
  myStepper.step(-rotations_per_resistor);
  delay(200);
  for(int i = 0; i<number_of_sets; i++)
  {
    if(stop == 0){    
    myStepper.step(number_of_resistors*rotations_per_resistor);
    delay(200);
    //Turn on both the servo motors for cutting.
    chop_belt1();
    nexLoop(nex_listen_list);
    }
  }
  Serial.println("Cutting 1 done");
}

void cut_resistors_2(int number_of_sets, int number_of_resistors)
{
  myStepper1.setSpeed(1000);
  myStepper1.step(rotations_per_resistor);
  delay(200);
  for(int i = 0; i<number_of_sets; i++)
  {
    if(stop == 0){    
    myStepper1.step(-number_of_resistors*rotations_per_resistor);
    delay(200);
    //Turn on both the servo motors for cutting.
    chop_belt2();
    nexLoop(nex_listen_list);
    }
  }
  Serial.println("Cutting 2 done");
}


void setup(void) {
  Serial.begin(9600);
  //Serial.begin(9600);
  nexInit();
  bt1.attachPop(bt1PopCallBack,&bt1);
  bt2.attachPop(bt2PopCallBack,&bt2);
  slow.attachPop(slowPopCallBack,&slow);
  medium.attachPop(mediumPopCallBack,&medium);
  fast.attachPop(fastPopCallBack,&fast);
  start.attachPop(startPopCallBack,&start);
  stop_yes.attachPop(stop_yesPopCallBack,&stop_yes);
  blt.attachPop(bltPopCallBack,&blt);
  forward.attachPop(forwardPopCallBack,&forward);
  back.attachPop(backPopCallBack,&back);
  

  motor1.attach(9);//yellow
  motor1.write(35);
  motor2.attach(10);//purple
  motor2.write(90);
  motor3.attach(11);//red
  motor3.write(150);
  motor4.attach(12);//green
  motor4.write(0);
  myStepper.setSpeed(1000);
  myStepper1.setSpeed(1000);
}

void loop() {
  nexLoop(nex_listen_list); 
  if(b1_done == 1 && b2_done == 1){
  Serial.print("page 4");
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
  delay(200);
  which_belt = 1;
  b1_sets = 0;
  b1_comps = 0;
  b2_sets = 0;
  b2_comps = 0;
  b1_done = 0;
  b2_done = 0;
  pb.setValue(0);}
}
