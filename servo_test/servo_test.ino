#include <Servo.h>
// Button 1
//  Grnd  |   4
//  ===========
//  null  |   null

// Joystick
//    Back
// Grnd | 5V | A0 | A1 | 2
//            (Nob)

// Servo
// Grnd | 3 | 5V


// Pins
int j_1_y = A1; // Joystick 1 y pin
int j_1_x = A0; // Joystick 1 x pin
int j_1_b = 2;  // Joystick 1 button pin
int b_1_pin = 4;// Button 1 pin

// Joystick 1
int j_1_y_state = 0; // Joystick 1 y state
int j_1_x_state = 0; // Joystick 1 x state
int j_1_b_state = 0; // Joystcik 1 button state

// Button 1
int b_1_state = 0;

// Servo
Servo servo;
int servoPin = 9;
int servoAngle = 0;

// Time Tracker
unsigned long time;
void setup() {
  // Joystick 1 Setup
  pinMode(j_1_y, INPUT);
  pinMode(j_1_x, INPUT);
  pinMode(j_1_b, INPUT_PULLUP);
  // Button 1 Setup
  pinMode(b_1_pin, INPUT_PULLUP);
  // Servo Setup
  servo.attach(servoPin);
  // Serial Communication
  Serial.begin(9600);

}
void updateJoysticks(){
  // get Joystick 1 button state
  j_1_b_state = digitalRead(j_1_b);
  // Get joystick 1 y val
  j_1_y_state = analogRead(j_1_y);
  // Get joystick 1 x val
  j_1_x_state = analogRead(j_1_x);
}
void updateSensors(){
  updateJoysticks();
  // Get button 1 state
  b_1_state = digitalRead(b_1_pin);
}
void printStates(){
    Serial.print("Joystick 1 x:");
    Serial.print(j_1_x_state);
    Serial.print("  y:");
    Serial.print(j_1_y_state);
    Serial.print(" b:");
    Serial.print(j_1_b_state);
    Serial.print("\nButton 1:");
    Serial.print(b_1_state);
    Serial.print("\nServo Angle:");
    Serial.println(servoAngle);
}
int convert(int value){
  // 0 = -100
  // 512 = 0
  // 1023 = 100
  if(value < 500 ){
    return -(100-int((value/500.0)*100));
  }else if(value > 524){
    return int((((value-524))/500.0)*100);
  }else{
    return 0;
  }
}
void setServoAngle(int angle){
  // Set servo angle and update tracking variabl
  servo.write(angle);
  servoAngle = angle;
  delay(15);
}
void updateServoPositions(){
  int rate = 0;
  // Convert to direction
  if(convert(j_1_x_state)<-50){
    rate = -1;
  }else if(convert(j_1_x_state)>50){
    rate = 1;
  }
  int min = 0;
  int max = 90;
  // Calc new angle
  int newAngle = servoAngle+rate;
  if(servoAngle+rate > max){
    newAngle = max;
  }
  if(servoAngle+rate < min){
    newAngle = min;
  }
  // Update servo position
  if(servoAngle != newAngle){
    setServoAngle(newAngle);
  }
  if(b_1_state ==0){
    setServoAngle(0);
  }
}
void loop() {
  // Update time
  time = millis();
  // get new sensor values
  updateSensors();
  // Update Servo Position
  updateServoPositions();
  // Print States once per second
  if(time % 500 == 0){
    printStates();
  }
}
