#define Vert A0
#define Rouge A1
#define Jaune A2
#define pinBouton 7

byte lastButtonState = LOW;
byte currentButtonState = LOW;
unsigned long lastButtonDebounceTime = 0;
unsigned long buttonDebounceDelay = 20;

void powerOffAllLEDs()
{
    digitalWrite(Vert, LOW);
    digitalWrite(Rouge, LOW);
    digitalWrite(Jaune, LOW);
}
void setup()
{
  Serial.begin(9600);
  pinMode(Vert, OUTPUT);
  pinMode(Rouge, OUTPUT);
  pinMode(Jaune, OUTPUT);
  pinMode(pinBouton, INPUT_PULLUP);
  powerOffAllLEDs();
}
void loop()
{
  boolean readValue = digitalRead(pinBouton);
  if (!readValue) { //button enfoncé
    Serial.write(1);
  }
  
  if (Serial.available() > 0) {
    int ledNumber = Serial.read() - '0';
    powerOffAllLEDs();
    
    switch (ledNumber) {
      case 1:
        digitalWrite(Vert, HIGH);
        break;
      case 2:
        digitalWrite(Rouge, HIGH);
        break;
      case 3:
        digitalWrite(Jaune, HIGH);
        break;
      default: 
        // wrong pin number, do nothing
        // all LEDs will be powered off
        break;
    }
  }
  else{
    powerOffAllLEDs();
  }
  
  delay(1000);
}
