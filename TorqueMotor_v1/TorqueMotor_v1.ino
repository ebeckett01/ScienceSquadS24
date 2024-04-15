
// Direction button pins
int fBPin = 13;
int bBPin = 12;
bool mftoggle = 0;
bool mbtoggle = 0;

// Torque value pins
int torqueVal = 2.5;
int torqueOut = torqueVal;
int tUpPin = 11;
int tDownPin = 10;
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
int Dir1Pin = 4;
int Dir2Pin = 3;
int enablePin = 5;

void setup() {
  pinMode(fBPin, INPUT_PULLUP);
  pinMode(bBPin, INPUT_PULLUP);

  pinMode(tUpPin, INPUT_PULLUP);
  pinMode(tDownPin, INPUT_PULLUP);

  pinMode(Dir1Pin, OUTPUT);
  pinMode(Dir2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  Serial.begin(9600);
}

void motorSettings() {
  speedVal = analogRead(vSpeedPin);
  speedVal = speedVal * (255/1023.0);
  analogWrite(enablePin, speedVal);
  
  if (digitalRead(fBPin) == LOW) {
    if (mftoggle == 0){
      digitalWrite(Dir1Pin, torqueOut);
      mftoggle = 1;
      digitalWrite(Dir2Pin, LOW);
    } else {
      digitalWrite(Dir1Pin, LOW);
      mftoggle = 0;
    }
  }
  if (digitalRead(bBPin) == LOW) {
    if (mbtoggle == 0){
      digitalWrite(Dir2Pin, torqueOut);
      mbtoggle = 1;
      digitalWrite(Dir1Pin, LOW);
    } else {
      digitalWrite(Dir2Pin, LOW);
      mbtoggle = 0;
    }
  }

}

void torqueSettings() {
  
  if (digitalRead(tUpPin) == LOW) {
    torqueVal = torqueVal + 0.5;
    Serial.println("Pressed");
    if (torqueVal > 5) {
      torqueVal = 5;
    }
  } else if (digitalRead(tDownPin) == LOW) {
    Serial.println("Pressed");
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
  Serial.print("Current speed: ");
  Serial.println(speedVal);
  Serial.print("Current torque: ");
  Serial.println(torqueOut);
}

void loop() {
  motorSettings();
  torqueSettings();
  printInfo();
}
