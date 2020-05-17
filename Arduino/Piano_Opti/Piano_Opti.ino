/*    Import library    */

#include <Adafruit_NeoPixel.h>  //Neopixel library


/*    Define    */

#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))  // calculate size of array
#define LED_PIN 8  // pin of Neopixel
#define LED_COUNT 30  // number of NeoPixels use

/*    Constants    */

// Motor constant
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

int motors[5][2] = {{stepPin1, dirPin1},
{stepPin2, dirPin2},
{stepPin3, dirPin3},
{stepPin4, dirPin4},
{stepPin5, dirPin5}};

/*    Variables    */
// NeoPixel strip object decoration
Adafruit_NeoPixel bande(LED_COUNT , LED_PIN , NEO_RGBW);
// Colors of Neopixels defining
uint32_t magenta = bande.Color(255, 0, 255, 0);
uint32_t greenishwhite = bande.Color(0, 64, 0, 64);

int myMelo[6] = {100, 100, 100, 100, 100, 100}; //Longest Array

//Motor Variables
int stepPin;
int dirPin;

int cocktails[8][5] = { {3, 4, 3, 0, 0},
                      {3, 0, 3, 0, 0},
                      {0, 5, 0, 0, 2},
                      {0, 0, 4, 0, 2},
                      {0, 0, 4, 0, 0}
                      };

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
bool reception;

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

  // Neopixels
  bande.begin();
  // Initialize all pixels to 'off'
  bande.show();

  // Debug
  pinMode(13, OUTPUT);

}

void loop() {
  
  while(!Serial.available() ){
    digitalWrite(13, LOW);
    }

  String data = Serial.readStringUntil(':');
  int int_data = data.toInt();
  
  i = 0;
  reception = true;
  while (reception){
      String data = Serial.readStringUntil(':');  // read receive value until ':' character
      int int_data = data.toInt(); // convert to int
      if (int_data != 0){
        myMelo[i] = int_data; //met les notes envoyées par la Raspbery et la liste de notes
        delay(50);
        i++;
      }
      else {
        reception = false;
      }
  }

  feedbackEndTransmission();

  turnoff_neopixel();

  play_melo();

  delay(3000);
  
  feedbackEndTransmission();

  delay(3000);

  feedbackEndTransmission();

  int cocktail = Serial.read() - '0';

  // Select the cocktail
  serveDrink(cocktail);
  feedbackEndTransmission();
  digitalWrite(13, LOW);

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
void serveDrink(int drink){
  for (i = 0; i <= ARRAY_SIZE(cocktails[drink-1]); i++){
    digitalWrite(13, HIGH);
    motor(computeLap(cocktails[drink-1][i]), i);
    digitalWrite(13, LOW);
  }
  delay(3000);
}

//Rotate the motor of <lap> laps
void motor(float lap, int motor){
  // Compute the number of steps
  value = lap*200;

  stepPin = motors[i][0];
  dirPin = motors[i][1];

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

void play_melo(){
 /*
  * Method which show the light sequence to play
  */
   for (int i = 0; i < ARRAY_SIZE(myMelo); i++) {
      if (myMelo[i] != 100){
        int led = myMelo[i] - 43;
        bande.setPixelColor(led, magenta);
        bande.show();
        delay(1000);
        turnoff_neopixel();
        delay(1000);
      }
   }
}

void turnoff_neopixel(){
  /*
   * Method which turn off the neopixel
   */
  bande.clear();
  bande.show();
}
