
// Direction button pins
int fBPin = ;
int bBPin = ;
bool dirToggle = 0;

// Torque value pins
int torqueVal = 2.5;
int torqueOut = HIGH;
int tUpPin = ;
int tDownPin = ;
/*
int R1in = A0; 
int R2out = A1;
int Vin = 0;
int Vout = 0;
float current = 0;
float Power = 0;
float avgPower = 0;
*/

// Motor speed and direction pin
int vSpeedPin = A3;
int speedVal = 0;
int Dir1Pin = ;
int Dir2Pin = ;
int enablePin = ;

void setup() {
  pinMode(fBpin, INPUT_PULLUP);
  pinMode(bBpin, INPUT_PULLUP);

  pinMode(tUpPin, INPUT_PULLUP);
  pinMode(tDownPin, INPUT_PULLUP);

  pinMode(Dir1Pin, OUTPUT);
  pinMode(Dir2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  Serial.begin(9600)
}

void motorSettings() {
  speedVal = analogRead(vSpeedPin);
  speedVal = speedVal * (255/1023.0);
  analogWrite(enablePin, speedVal);
  
  if (digitalRead(fBPin) == LOW) {
    digitalWrite(Dir2Pin, LOW);
    digitalWrite(Dir1Pin, torqueOut);
  } else if (digitalRead(bBPin) == LOW) {
    digitalWrite(Dir2Pin, torqueOut);
    digitalWrite(Dir1Pin, LOW);
  }

}

void torqueSettigs() {
  
  if (digitalRead(tUpPin) == LOW) {
    torqueVal = torqueVal + 0.5;
    if (torqueVal > 5) {
      torqueVal = 5;
    }
  } else if (digitalRead(tDownPin) == LOW) {
    torqueVal = torqueVal - 0.5;
    if (torqueVal < 0.5) {
      torqueVal = 0.5;
    }
  }

  /*
  Vin = analogRead(R1in) * (5/1023.0);
  Vout = analogRead(R1out) * (5/1023.0);
  delay(10);
  current = (Vout / (10 * 1000));
  Power =  current * Vout;
  */

  torqueOut = torqueVal;

}

void printInfo() {
  Serial.print("Current speed: ")
  Serial.println(speedVal)
  Serial.print("Current torque: ")
  Serial.println(torqueOut)
}

void loop() {
  motorSettings();
  torqueSettings();
  printInfo();
}
