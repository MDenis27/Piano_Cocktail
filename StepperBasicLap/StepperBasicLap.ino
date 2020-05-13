// Arduino stepper motor control code

#include <Stepper.h> // Include the header file

// change this to the number of steps on your motor
#define STEPS 32

// create an instance of the stepper class using the steps and pins
Stepper stepper(STEPS, 8, 10, 9, 11);

float val = 0;
float lap = 0;

void setup() {
  Serial.begin(9600);
  //Set the speed
  stepper.setSpeed(200);
}

void loop() {

  if (Serial.available()>0)
  {
    lap = Serial.parseInt();
    Serial.println(lap);
    rotationLap(lap);
  }
 

}

void rotationLap(float lap) {
  val = lap*2048;
  Serial.println(val);
  stepper.step(val);
}
