#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//Button Pins 
const int btnPin1 = 6;
const int btnPin2 = 5;
const int btnPin3 = 4;
const int btnPin4 = 3;

// 4 channel Relay pins
const int ledPin1 = A5;
const int ledPin2 = A4;
const int ledPin3 = A3;
const int ledPin4 = A2;


//  4 channel Relay States (HIGH = OFF , LOW=ON) .
int ledState1 = HIGH;
int ledState2 = HIGH;
int ledState3 = HIGH;
int ledState4 = HIGH;


// BUTTON STATES to store present button state or changes.
int btnState1;
int btnState2;
int btnState3;
int btnState4;

// Previous button State are stored in this variable
int lastBtnState1 = HIGH;
int lastBtnState2 = HIGH;
int lastBtnState3 = HIGH;
int lastBtnState4 = HIGH;

// Lists that store all variables
int btnPin[] = {btnPin1, btnPin2, btnPin3, btnPin4};
int ledPin[] = {ledPin1, ledPin2, ledPin3, ledPin4};
int ledState[] = {ledState1, ledState2, ledState3, ledState4};
int btnState[] = {btnState1, btnState2, btnState3, btnState4};
int lastBtnState[] = {lastBtnState1, lastBtnState2, lastBtnState3,  lastBtnState4};


// The following variables are unsigned longs
// because the time, measured in milliseconds,
// will quickly become a bigger number than can
// can be stored in an int.

unsigned long lastDebounceTime = 0; // Last time the output pin was toggled
unsigned long debounceDelay = 50;

// each reading will store the changes in th buttons.
int reading1;
int reading2;
int reading3;
int reading4;

char BtState;

void setup() {

  for (int i = 0; i < 4; i++) {
    pinMode(btnPin[i], INPUT);
    pinMode(ledPin[i], OUTPUT);
    digitalWrite(ledPin[i], ledState[i]);
  }

  Serial.begin(9600);
  dht.begin();

  Serial.println("------------------");
  Serial.println(" Arduino has Initialized! ");
  Serial.println("------------------");
}


void loop() {
  CheckState();
}

void BT() {
  while (Serial.available() > 0) {
    BtState = Serial.read();

    if (BtState == '1') {
      AllOn();
      Serial.println(" All Lights ON");
      delay(1);
    }

    if (BtState == '2') {
      AllOff();
      Serial.println(" All Lights OFF");
      delay(1);
    }

    if (BtState == '3') {
      ledState1 = LOW;
      lastBtnState1 = LOW;
      digitalWrite(ledPin1, ledState1);
      Serial.println("Light1 ON");
      delay(1);
    }

    if (BtState == '4') {
      ledState2 = LOW;
      lastBtnState2 = LOW;
      digitalWrite(ledPin2, ledState2);
      Serial.println("Light2 ON");
      delay(1);
    }

    if (BtState == '5') {
      ledState3 = LOW;
      lastBtnState3 = LOW;
      digitalWrite(ledPin3, ledState3);
      Serial.println("Light3 ON");
      delay(1);
    }

    if (BtState == '6') {
      ledState4 = LOW;
      lastBtnState4 = LOW;
      digitalWrite(ledPin4, ledState4);
      Serial.println("Light4 ON");
      delay(1);
    }

    if (BtState == '7') {
      ledState1 = HIGH;
      lastBtnState1 = HIGH;
      digitalWrite(ledPin1, ledState1);
      Serial.println("Lights1 OFF");
      delay(1);
    }

    if (BtState == '8') {
      ledState2 = HIGH;
      lastBtnState2 = HIGH;
      digitalWrite(ledPin2, ledState2);
      Serial.println("Lights2 OFF");
      delay(1);
    }

    if (BtState == '9') {
      ledState3 = HIGH;
      lastBtnState3 = HIGH;
      digitalWrite(ledPin3, ledState3);
      Serial.println("Lights3 OFF");
      delay(1);
    }

    if (BtState == '0') {
      ledState4 = HIGH;
      lastBtnState4 = HIGH;
      digitalWrite(ledPin4, ledState4);
      Serial.println("Lights4 OFF");
      delay(1);
    }

    if (BtState == 'T') {
      Temp();
      delay(1);
    }




  }
}

void CheckState() {
  BT();
  reading1 = digitalRead(btnPin1);
  reading2 = digitalRead(btnPin2);
  reading3 = digitalRead(btnPin3);
  reading4 = digitalRead(btnPin4);
  Main();
}

void Main() {
  if ((reading1 != lastBtnState1) || (reading2 != lastBtnState2) || (reading3 != lastBtnState3) || (reading4 != lastBtnState4))
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading1 != btnState1) {
      btnState1 = reading1;

      if ((btnState1 == LOW)) {
        ledState1 = !ledState1;
      }
    }

    if (reading2 != btnState2) {
      btnState2 = reading2;

      if ((btnState2 == LOW)) {
        ledState2 = !ledState2;
      }
    }

    if (reading3 != btnState3) {
      btnState3 = reading3;

      if ((btnState3 == LOW)) {
        ledState3 = !ledState3;
      }
    }

    if (reading4 != btnState4) {
      btnState4 = reading4;

      if ((btnState4 == LOW)) {
        ledState4 = !ledState4;
      }
    }

  }

  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);
  digitalWrite(ledPin3, ledState3);
  digitalWrite(ledPin4, ledState4);

  lastBtnState1 = reading1;
  lastBtnState2 = reading2;
  lastBtnState3 = reading3;
  lastBtnState4 = reading4;
}

void AllOn() {
  ledState1 = LOW;
  ledState2 = LOW;
  ledState3 = LOW;
  ledState4 = LOW;

  lastBtnState1 = LOW;
  lastBtnState2 = LOW;
  lastBtnState3 = LOW;
  lastBtnState4 = LOW;

  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);
  digitalWrite(ledPin3, ledState3);
  digitalWrite(ledPin4, ledState4);
}

void AllOff() {

  for (int i = 0; i < 4; i++) {
    ledState[i]=HIGH;
    lastBtnState[i]=HIGH;
    digitalWrite(ledPin[i], ledState[i]);
  }

  
  ledState1 = HIGH;
  ledState2 = HIGH;
  ledState3 = HIGH;
  ledState4 = HIGH;

  lastBtnState1 = HIGH;
  lastBtnState2 = HIGH;
  lastBtnState3 = HIGH;
  lastBtnState4 = HIGH;

  digitalWrite(ledPin1, ledState1);
  digitalWrite(ledPin2, ledState2);
  digitalWrite(ledPin3, ledState3);
  digitalWrite(ledPin4, ledState4);
}

void Temp() {
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(" %");
  Serial.println(" ");

  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println(" ");

  Serial.print(F("Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.println(" ");
}
