//same libraries and object creation as your transmitter
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
// Create Receiver object
RF24 radio(9, 8);  // CE, CSN
// Data Packet structer must match transceiver
struct DataPacket {
  int j1X;
  int j1Y;
  int j1Switch;
  int j2X;
  int j2Y;
  int j2Switch;
  int b1;
  int b2;
  int p;
};
DataPacket data;
// Direction enum used for motors
enum direction{FORWARD, REVERSE, STOP};
//address through which two modules communicate.
const byte address[6] = "83287";
// Constants
const int motor_max = 255; // Max speeed for a motor (ie 100%)
/*  L293D Setup
Motor 1               Motor 2
         Cresent
M1 PWM  1       16   Battery +ve
M1 0/1  2       15   M2 0/1
M1 +ve  3       14   M2 +ve
GND     4       13   GND
GND     5       12   GND
M1 -ve  6       11   M2 -ve
M1 1/0  7       10   M2 1/0
Bat +ve 8        9   M2 PWM

*/
// Motor 1 pins
const int enable1 = 0; // M1 PWM
const int drive1A = 0; // M1 0/1
const int drive1B = 0; // M1 1/0
// Motor 2 pins
const int enable2 = 0; // M2 PWM
const int drive2A = 0; // M2 0/1
const int drive2B = 0; // M2 1/0
// Servo pins
const int servo1Pin = 0;
const int servo2Pin = 0;
// Servo Objects
Servo servo1;
Servo servo2;
void setup() {
  // Motor 1 Setup
  pinMode(enable1, OUTPUT);
  pinMode(drive1A, OUTPUT);
  pinMode(drive1B, OUTPUT);
  // Motor 2 Setup
  pinMode(enable2, OUTPUT);
  pinMode(drive2A, OUTPUT);
  pinMode(drive2B, OUTPUT);
  // Servo 1 Setup
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  // Radio Setup
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(0, address);
  radio.startListening();
  // Serial Setup
  Serial.begin(9600);
}
void setServoAngle(int servo, int angle){
  // TODO
}
void setMotorSpeed(int motor,int speed, direction dir){
  // Select the pins for the correct motor
  int motorSpeedPin = -1;
  int drive1 = -1;
  int drive2 = -1;
  if(motor == 1){
    motorSpeedPin = enable1;
    drive1 = drive1A;
    drive2 = drive1B;
  }else if(motor ==2){
    motorSpeedPin = enable2;
    drive1 = drive2A;
    drive2 = drive2B;
  }
  // Convert direction for motor
  if(dir == FORWARD){
    digitalWrite(drive1, HIGH);
    digitalWrite(drive2, LOW);
  }else if(dir == REVERSE){
    digitalWrite(drive1, LOW);
    digitalWrite(drive2, HIGH);
  }else{
    digitalWrite(drive1, LOW);
    digitalWrite(drive2, LOW);
  }
  // Output motor speed
  analogWrite(motorSpeedPin, speed);
}
void printDataPacket(){
    // Log data being sent
    Serial.print("Joystick 1 x:");
    Serial.print(data.j1X);
    Serial.print(" y:");
    Serial.print(data.j1Y);
    Serial.print(" b:");
    Serial.print(data.j1Switch);
    Serial.print("\nJoystick 2 x:");
    Serial.print(data.j2X);
    Serial.print(" y:");
    Serial.print(data.j2Y);
    Serial.print(" b:");
    Serial.print(data.j2Switch);
    Serial.print("\nButton 1:");
    Serial.print(data.b1);
    Serial.print("\nButton 2:");
    Serial.print(data.b2);
    Serial.print("\nPotentiometer:");
    Serial.println(data.p);
}
void loop() {
  if (radio.available()) {//if a signal is available
    radio.read(&data, sizeof(DataPacket));//read signal being sent
    printDataPacket();
  }
}