// Arduino stepper motor control code

#include <Stepper.h> // Include the header file

// change this to the number of steps on your motor
#define STEPS 32

// create an instance of the stepper class using the steps and pins
Stepper stepper(STEPS, 8, 10, 9, 11);

float val = 0;
float angle = 0;

void setup() {
  Serial.begin(9600);
  //Set the speed
  stepper.setSpeed(200);
}

void loop() {

  if (Serial.available()>0)
  {
    angle = Serial.parseInt();
    Serial.println(angle);
    rotationAngle(angle);
    //stepper.step(val);
    //Serial.println(val); //for debugging
  }
 

}

void rotationAngle(float angle) {
  val = (angle/360)*2048;
  Serial.println(val);
  stepper.step(val);
}
