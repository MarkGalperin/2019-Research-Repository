#include <Wire.h>
#include <Adafruit_MotorShield.h>

char cmd;
int num_steps = 0;
int spd = 0;
int step_type = 4; //MICROSTEP

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Connect a stepper motor with 25 steps per revolution to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(400, 2);

int get_int() { //converts whatever is in the serial buffer to an integer
  char buff[8];
  int buff_idx = 0;
  while (Serial.available()) {
    buff[buff_idx] = Serial.read();
    buff_idx++;
  }
  return atoi(buff);
}

void setup() {
  // set up Serial library at 115200 bps
  // MAKE SURE YOU SET BAUD RATE IN SERIAL MONITOR TO 115200!!!!!!!!
  Serial.begin(115200);

  // print out user instructions
  Serial.println("STEPPER TEST COMMANDS");
  Serial.println("---------------------");
  Serial.println("TAKE STEPS:        'f' or 'b' followed by number of forward or backward steps to take");
  Serial.println("CHANGE SPEED:      's' followed by desired speed (default 10 RPM)");
  Serial.println("CHANGE STEP TYPE:  't' followed by step type-  1: SINGLE  2: DOUBLE  3: INTERLEAVE  4: MICROSTEP(default)");

  AFMS.begin();  // init motor shield with the default frequency 1.6KHz
  myMotor->setSpeed(10);  // 1 rpm
  myMotor->release();     // make sure coils are disengaged
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()) {

    delay(1000); //wait one second to make sure everything has been recieved
    cmd = Serial.read();

    switch (cmd) {
      case 'f':   //move Forward
        num_steps = get_int();
        Serial.print("Forward:\t");
        Serial.println(num_steps);
        myMotor->step(num_steps, FORWARD, step_type);
        myMotor->release();
        break;
      case 'b':   //move Backward
        num_steps = get_int();
        Serial.print("Backward:\t");
        Serial.println(num_steps);
        myMotor->step(num_steps, BACKWARD, step_type);
        myMotor->release();
        break;
      case 's':   //set Speed
        spd = get_int();
        Serial.print("Set Speed:\t");
        Serial.println(spd);
        myMotor->setSpeed(spd);
        myMotor->release();
        break;
      case 't':  //step Type
        step_type = get_int();
        Serial.print("Step Type:\t");
        Serial.println(step_type);
        break;
      default:
        Serial.println("Unexpected command. Type 'f', 'b', 's', or 't' followed by a number, then press ENTER.");
    }
  }
}







