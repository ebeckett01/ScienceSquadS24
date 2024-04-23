
// Direction button pins
int fBPin = 13;
int bBPin = 12;
bool mftoggle = 0;
bool mbtoggle = 0;

// Torque value pins
int torqueVal = 5;
int tUpPin = 11;
int tDownPin = 10;

int R1in = A0; 
int R2out = A1;
int Vin = 0;
int Vout = 0;
float current = 0;
float Power = 0;
float avgpowercalculation = 0;
int power_calc_iteration = 0;
float avgPower = 0;
float powerThreshold = 22000; // mW


// Motor speed and direction pin
int vSpeedPin = A3;
int speedVal = 0;
int Dir1Pin = 4;
int Dir2Pin = 3;
int enablePin = 5;

// Button Variables
unsigned long time = 0;
unsigned long debounceTime = 50;
unsigned long fBPress =0;
unsigned long bBPress =0;
unsigned long tuPress =0;
unsigned long tdPress =0;
// Torque Stall Settings
int torque[] = {
  10000, // Setting 1
  11000, // Setting 2
  12000, // Setting 3
  13000, // Setting 4
  14000, // Setting 5
  15000, // Setting 6
  16000, // Setting 7
  17000, // Setting 8
  18000, // Setting 9
  20000, // Setting 10
};
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
  time = millis();
  speedVal = analogRead(vSpeedPin);
  speedVal = speedVal * (255/1023.0);
  //analogWrite(enablePin, speedVal);
  if(time-fBPress > debounceTime){
    if (digitalRead(fBPin) == LOW) {
      Serial.println("Pressed");
      if (mftoggle == 0){
        digitalWrite(Dir1Pin, HIGH);
        mftoggle = 1;
        digitalWrite(Dir2Pin, LOW);
      } else {
        digitalWrite(Dir1Pin, LOW);
        mftoggle = 0;
      }
    }
  }
  if(time - bBPress > debounceTime){
    if (digitalRead(bBPin) == LOW) {
      Serial.println("Pressed");
      if (mbtoggle == 0){
        digitalWrite(Dir2Pin, HIGH);
        mbtoggle = 1;
        digitalWrite(Dir1Pin, LOW);
      } else {
        digitalWrite(Dir2Pin, LOW);
        mbtoggle = 0;
      }
    }
  }

}

void torqueSettings() {
  if(time - tuPress > debounceTime && time - tdPress >debounceTime){
    if (digitalRead(tUpPin) == LOW) {
      torqueVal++;
      Serial.println("Pressed");
      if (torqueVal > 10) {
        torqueVal = 9;
      }
      powerThreshold = torque[torqueVal];
    } else if (digitalRead(tDownPin) == LOW) {
      Serial.println("Pressed");
      torqueVal--;
      if (torqueVal < 0) {
        torqueVal = 0;
      }
      powerThreshold = torque[torqueVal];
    }
  }

  
  Vin = analogRead(R1in);
  Vout = analogRead(R2out);
  delay(10);
  current = ((Vin-Vout)/10)*1000;
  Power =  (current * Vout)/1000;

  if (power_calc_iteration < 15){
    avgpowercalculation = avgpowercalculation + Power;
    power_calc_iteration++;
  }
  else {
    avgPower = avgpowercalculation/15;
    power_calc_iteration = 0;
    avgpowercalculation = 0;
  }
  //Serial.println(abs(avgPower));
  if (abs(avgPower) > powerThreshold) {
    analogWrite(enablePin, 0);
  } else {
    analogWrite(enablePin, speedVal);
  }

}

void printInfo() {
  //Serial.print("Current speed: ");
  //Serial.println(speedVal);
  //Serial.print("Current torque: ");
  //Serial.println(torqueVal);
  //Serial.println("Power: ");
  //Serial.println(avgPower);

  //Serial.println("Vin: ");
  //Serial.println(Vin);
  //Serial.println("Vout: ");
  //Serial.println(Vout);
}

void loop() {
  motorSettings();
  torqueSettings();
  printInfo();
}
