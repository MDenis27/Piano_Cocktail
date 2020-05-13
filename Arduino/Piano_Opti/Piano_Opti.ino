const int stepPin1 = 11;
const int dirPin1 = 12;

const int stepPin2 = 9;
const int dirPin2 = 10;

const int stepPin3 = 6;
const int dirPin3 = 7;

const int stepPin4 = 4;
const int dirPin4 = 5;

const int stepPin5 = 2;
const int dirPin5 = 3;

int stepPin;
int dirPin;

//{Tequila, Gin, Vodka, Sprite, Ginger ale}
//Tequila
int cocktail1[5] = {300, 0, 300, 0, 0};
//Gin
int cocktail2[5] = {300, 0, 300, 0, 0};
//London Mule (Gin & Ginger Ale)
int cocktail3[5] = {0, 50, 0, 0, 200};
//Moskow Mule (Vodka & Ginger)
int cocktail4[5] = {0, 0, 50, 0, 200};
//Vodka
int cocktail5[5] = {0, 0, 40, 0, 0};
//Gimlet (Gin & Sprite)
int cocktail6[5] = {0, 50, 0, 200, 0};
//Vodka Sprite
int cocktail7[5] = {0, 0, 50, 200, 0};
//Tequila Sprite
int cocktail8[5] = {50, 0, 0, 200, 0};


float value = 0;
float y;
float lap;
int val = 0;
int i;

void feedbackEndTransmission()
{
  Serial.write(1);
}

void setup() {
  Serial.begin(9600);
  
  // Sets the motors' pins as Outputs
  pinMode(stepPin1,OUTPUT);
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT);
  pinMode(dirPin2,OUTPUT);
  pinMode(stepPin3,OUTPUT);
  pinMode(dirPin3,OUTPUT);
  pinMode(stepPin4,OUTPUT);
  pinMode(dirPin4,OUTPUT);
  pinMode(stepPin5,OUTPUT);
  pinMode(dirPin5,OUTPUT);

}

void loop() {

  // Debut comminication with Rasp
  if (Serial.available() > 0) {
    int cocktail = Serial.read() - '0';

    // Select the cocktail
    switch (cocktail) {
      case 1:
        serveDrink(cocktail1);
        break;
      case 2:
        serveDrink(cocktail2);
        break;
      case 3:
        serveDrink(cocktail3);
        break;
      case 4:
        serveDrink(cocktail4);
        break;
      case 5:
        serveDrink(cocktail5);
        break;
      case 6:
        serveDrink(cocktail6);
        break;
      case 7:
        serveDrink(cocktail7);
        break;
      case 8:
        serveDrink(cocktail8);
        break;
      default:
        break;
    }
    feedbackEndTransmission();
  }

}

//Compute lap from ml
float computeLap(int ml) {
  lap = 0;
  
  if (ml != 0){
    y = (float) ml;
    lap = (y - 0.3393)/0.5141;
  }
  return lap;
}

//Serve drink from table
void serveDrink(int tab[]){
  for (i = 0; i <= 5; i++){
    motor(computeLap(tab[i]), i+1);
  }
}

//Rotate the motor of <lap> laps
void motor(float lap, int motor){
  // Compute the number of steps
  value = lap*200;

  // Choose the right motor
  switch (motor) {
      case 1:
        dirPin = dirPin1;
        stepPin = stepPin1;
        break;
      case 2:
        dirPin = dirPin2;
        stepPin = stepPin2;
        break;
      case 3:
        dirPin = dirPin3;
        stepPin = stepPin3;
        break;
      case 4:
        dirPin = dirPin4;
        stepPin = stepPin4;
        break;
      case 5:
        dirPin = dirPin5;
        stepPin = stepPin5;
        break;
      default:
        break;
    }

  // Decide the sens of rotation
  digitalWrite(dirPin,LOW);
  if (lap < 0) {
    digitalWrite(dirPin,HIGH);
    value = - value;
  }

  //Turn <val> step
  val = (int) value;
  Serial.println(val);
    for(int x = 0; x < val; x++) {
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(500);
      digitalWrite(stepPin,LOW);
      delayMicroseconds(500);
    }
}
