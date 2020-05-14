/*    Import library    */

#include <Adafruit_NeoPixel.h>  //Neopixel library


/*    Define    */

#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))  // calculate size of array
#define LED_PIN 6  // pin of Neopixel
#define LED_COUNT 30  // number of NeoPixels use

/*    Constants    */

// Motor constant
const int stepPin1 = 2;
const int dirPin1 = 3;

const int stepPin2 = 4;
const int dirPin2 = 5;

const int stepPin3 = 6;
const int dirPin3 = 7;

const int stepPin4 = 9;
const int dirPin4 = 10;

const int stepPin5 = 11;
const int dirPin5 = 12;


/*    Variables    */

Adafruit_NeoPixel bande(LED_COUNT , LED_PIN , NEO_RGBW); // NeoPixel strip object decalaration
// Colors of Neopixels defining
uint32_t magenta = bande.Color(255, 0, 255, 0);
uint32_t greenishwhite = bande.Color(0, 64, 0, 64);

int myMelo[5]; //array which content melody (size = 5)

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
float temp;
float lap = 0;
int val = 0;
int i;

byte lastButtonState = LOW;
byte currentButtonState = LOW;
unsigned long lastButtonDebounceTime = 0;
unsigned long buttonDebounceDelay = 20;


/*    Setup    */

void setup() {
  Serial.begin(9600);
  
  // Sets the two pins of motors as Outputs
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
  bande.show(); // Initialize all pixels to 'off'
}


/*    Loop    */

void loop() {

  if (Serial.available() > 0) {
    for (int i = 0; i < 5; i++) {  // loop to fill array of melody (size = 5)
        String data = Serial.readStringUntil(':');  // read receive value until ':' character
        int int_data = data.toInt(); // convert to int
        myMelo[i] = int_data; //met les notes envoyées par la Raspbery et la liste de notes
        delay(50);
    }

    turnoff_neopixel();

    play_melo();

    delay(5000);  // waiting for receiving number of cocktail from rapsberry
    
    int nr_cocktail = Serial.read() - '0';
    Serve(nr_cocktail);
    
  }

  delay(5000);  // waiting for taking off the glass of user

}


/*    Functions declaration    */

float computeLap(int ml) {
  /*
   * Method which Compute lap from ml
   */
  if (ml != 0){
    temp = (float) ml;
    lap = (temp - 0.33)/2;
  }
  else {
    lap = 0;
  }
  return lap;
}

void serveDrink(int tab[]){
  /*
   * Method which make a cocktail
   */
  for (i = 0; i <= 5; i++){
    Motor(computeLap(tab[i]), i+1);
  }
}

void Motor(float lap, int motor){
  /*
   * Method which turn the motor to make a cocktail
   */
  value = lap*200;

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

  
  if (lap > 0) {
    digitalWrite(dirPin,LOW);
  }
  else {
    digitalWrite(dirPin,HIGH);
    value = -value;
  }

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
  bande.setPixelColor(myMelo[i], magenta);
  bande.show();
  delay(1000);
  turnoff_neopixel();
  delay(1000);
  }
}

void feedbackEndTransmission()
{
  Serial.write(1);
}

void Serve(int cocktail){
  /*
   * Method which serve the cocktail chosen
   */
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

void turnoff_neopixel(){
  /*
   * Method which turn off the neopixel
   */
  bande.clear();
  bande.show();
}
