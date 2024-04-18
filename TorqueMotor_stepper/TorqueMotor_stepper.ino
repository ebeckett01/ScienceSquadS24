#include <Stepper.h>
// Direction button pins
int fBPin = 3;
int bBPin = 4;
bool mftoggle = 0;
bool mbtoggle = 0;

// Torque value pins
int torqueVal = 5;
int tUpPin = 5;
int tDownPin = 6;

int R1in = A0; 
int R2out = A1;
int Vin = 0;
int Vout = 0;
float current = 0;
float Power = 0;
float avgpowercalculation = 0;
int power_calc_iteration = 0;
float avgPower = 0;
float powerThreshold = ; // mW


// Motor speed and direction pin
const int stepsPerRevolution = 2048;
int currentAngle = 0;
bool stop = false;
Stepper myStepper(stepsPerRevolution, 8,19,9,11);

void setup() {
  pinMode(fBPin, INPUT_PULLUP);
  pinMode(bBPin, INPUT_PULLUP);

  pinMode(tUpPin, INPUT_PULLUP);
  pinMode(tDownPin, INPUT_PULLUP);

  myStepper.setSpeed(10);
  Serial.begin(9600);
}

void motorSettings() {
  speedVal = analogRead(vSpeedPin);
  speedVal = speedVal * (255/1023.0);
  analogWrite(enablePin, speedVal);
  
  if (digitalRead(fBPin) == LOW) {
    if (mftoggle == 0){
      currentAngle=stepperGoTo((currentAngle+1)%1023, currentAngle);
      mftoggle = 1;
    } else {
      mftoggle = 0;
    }
  }
  if (digitalRead(bBPin) == LOW) {
    if (mbtoggle == 0){
      currentAngle=stepperGoTo((currentAngle+1022)%1023, currentAngle);
      mbtoggle = 1;
    } else {
      mbtoggle = 0;
    }
  }

}

void torqueSettings() {
  
  if (digitalRead(tUpPin) == LOW) {
    torqueVal++;
    //Serial.println("Pressed");
    if (torqueVal > 10) {
      torqueVal = 10;
    }
  } else if (digitalRead(tDownPin) == LOW) {
    //Serial.println("Pressed");
    torqueVal--;
    if (torqueVal < 1) {
      torqueVal = 1;
    }
  }

  
  Vin = analogRead(R1in) * (5/1023.0);
  Vout = analogRead(R1out) * (5/1023.0);
  delay(10);
  current = (Vout / (10 * 1000));
  Power =  current * Vout;

  if (power_calc_iteration < 5){
    avgpowercalculation = avgpowercalculation + Power;
    power_calc_iteration++;
  }
  else {
    avgPower = avgpowercalculation/5;
    power_calc_iteration = 0;
    avgpowercalculation = 0;
  }
  
  if (avgPower < powerThreshold) {
    stop = true;
  }else{
    stop = false;
  }

}

void printInfo() {
  Serial.print("Current speed: ");
  Serial.println(speedVal);
  Serial.print("Current torque: ");
  Serial.println(torqueOut);
  Serial.println("Power: ");
  Serial.println(avgPower);
}

void loop() {
  motorSettings();
  torqueSettings();
  printInfo();
}
