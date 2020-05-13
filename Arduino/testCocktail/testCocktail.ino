#define pinBouton 8

const int stepPin1 = 2;
const int dirPin1 = 3;

const int stepPin2 = 4;
const int dirPin2 = 5;

const int stepPin3 = 6;
const int dirPin3 = 7;

int cocktail1[3] = {5, 20, 0};
int cocktail2[3] = {5, 5, 5};

float value = 0;
float temp;
int cocktail = 0;
int val = 0;
float lap = 1;

byte lastButtonState = LOW;
byte currentButtonState = LOW;
unsigned long lastButtonDebounceTime = 0;
unsigned long buttonDebounceDelay = 20;

void feedbackEndTransmission()
{
  Serial.write(1);
}

void setup() {
  Serial.begin(9600);
  // Sets the two pins as Outputs
  pinMode(stepPin1,OUTPUT);
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT);
  pinMode(dirPin2,OUTPUT);
  pinMode(stepPin3,OUTPUT);
  pinMode(dirPin3,OUTPUT);
  pinMode(pinBouton, INPUT_PULLUP);

}

void loop() {
  
  if (Serial.available() > 0) {
    cocktail = Serial.parseInt();
    Serial.print("cocktail number:");
    Serial.println(cocktail);
    
    switch (cocktail) {
      case 1:
        serveDrink(cocktail1);
        break;
      case 2:
        serveDrink(cocktail2);
        break;
      default:
        break;
    }
    feedbackEndTransmission();
  }

}

//Compute lap from ml
float computeLap(int ml) {
  if (ml != 0){
    temp = (float) ml;
    Serial.print("temp:");
    Serial.print(temp);
    lap = (temp - 0.33)/2;
  }
  else {
    lap = 0;
  }
  Serial.print("ml:");
  Serial.print(ml);
  Serial.print("lap:");
  Serial.print(lap);
  return lap;
}

//Serve drink from table
void serveDrink(int tab[]){
  Motor1(computeLap(tab[0]));
  Motor2(computeLap(tab[1]));
  Motor3(computeLap(tab[2]));
}

void Motor1(float lap){
  value = lap*200;
  
  if (lap > 0) {
    digitalWrite(dirPin1,LOW);
  }
  else {
    digitalWrite(dirPin1,HIGH);
    value = -value;
  }

  val = (int) value;
  Serial.print("val1:");
  Serial.println(val);
    for(int x = 0; x < val; x++) {
      digitalWrite(stepPin1,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin1,LOW);
      delayMicroseconds(500);
    }
}

void Motor2(float lap){
  value = lap*200;
  
  if (lap > 0) {
    digitalWrite(dirPin2,LOW);
  }
  else {
    digitalWrite(dirPin2,HIGH);
    value = -value;
  }

  val = (int) value;
  Serial.print("val2:");
  Serial.println(val);
    for(int x = 0; x < val; x++) {
      digitalWrite(stepPin2,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin2,LOW);
      delayMicroseconds(500);
    }
}

void Motor3(float lap){
  value = lap*200;
  
  if (lap > 0) {
    digitalWrite(dirPin3,LOW);
  }
  else {
    digitalWrite(dirPin3,HIGH);
    value = -value;
  }

  val = (int) value;
  Serial.print("val3:");
  Serial.println(val);
    for(int x = 0; x < val; x++) {
      digitalWrite(stepPin3,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin3,LOW);
      delayMicroseconds(500);
    }
}
