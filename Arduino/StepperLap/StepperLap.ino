 /*     Simple Stepper Motor Control Exaple Code
   * 
   *  by Dejan Nedelkovski, www.HowToMechatronics.com
   * 
 */
     
// defines pins numbers
const int stepPin = 2;
const int dirPin = 4;

float value = 0;
float lap = 0;
     
void setup() {
  Serial.begin(9600);
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
}

void loop() {
  if (Serial.available()>0)
  {
    lap = Serial.parseFloat();
    Serial.println(lap);
    rotateLap(lap);
  }

  delay(1000);

}

void rotateAngle(float angle){
  value = (angle/360)*200;

  digitalWrite(dirPin, LOW);
  if (angle < 0) {
    digitalWrite(dirPin,HIGH);
    value = -value;
  }
 
  Serial.println(value);
    for(int x = 0; x < value; x++) {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(500);
    }
}

void rotateLap(float lap){
  value = lap*200;
  
  digitalWrite(dirPin,LOW);
  if (lap < 0) {
    digitalWrite(dirPin,HIGH);
    value = - value;
  }

  val = (int) value;
  Serial.println(val);
    for(int x = 0; x < val; x++) {
      Serial.println(x);
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(500);
    }
}
