//include the necessary libraries for the RF24 Tx/Rx
//Tx = transmitter
//Rx = reciever
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create the RF24 object
RF24 radio(9, 8);  // CE, CSN
const int xPin = 0;
const int yPin = 1;
const int jSW = 2;
const int nSW = 4;
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
const byte address[6] = "83287";
// Sensor Pins
int j_1_y = A1; // Joystick 1 y pin
int j_1_x = A0; // Joystick 1 x pin
int j_1_b = 10;  // Joystick 1 button pin
int j_2_y = A3; // Joystick 2 y pin
int j_2_x = A2; // Joystick 2 x pin
int j_2_b = 7;  // Joystick 2 button pin
int p_pin = A4; // Potentiometer pin
int b_1_pin = 2;// Button 1 pin
int b_2_pin = 4;// Button 2 pin

// State Trackers
// Joystick 1
int j_1_y_state = 0; // Joystick 1 y state
int j_1_x_state = 0; // Joystick 1 x state
int j_1_b_state = 0; // Joystcik 1 button state
// Joystick 2
int j_2_y_state = 0; // Joystick 1 y state
int j_2_x_state = 0; // Joystick 1 x state
int j_2_b_state = 0; // Joystcik 1 button state
// Potentiometer
int p_state = 0;
// Button 1
int b_1_state = 0;
// Button 2
int b_2_state = 0;
// time tracker
unsigned long time;
void setup() {
  // Joystick 1 Setup
  pinMode(j_1_y, INPUT);
  pinMode(j_1_x, INPUT);
  pinMode(j_1_b, INPUT_PULLUP);
  // Joystick 2 Setup
  pinMode(j_2_y, INPUT);
  pinMode(j_2_x, INPUT);
  pinMode(j_2_b, INPUT_PULLUP);
  // Potentiomete Setup
  pinMode(p_pin, INPUT); 
  // Button 1 Setup
  pinMode(b_1_pin, INPUT_PULLUP);
  // Button 2 Setup
  pinMode(b_2_pin, INPUT_PULLUP);
  // Transmitter Setup
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(address);
  radio.stopListening();
  Serial.begin(9600);//you better know what this does
  Serial.println("Start");
}
void updateJoysticks(){
  // get Joystick 1 button state
  j_1_b_state = digitalRead(j_1_b);
  // Get joystick 1 y val
  j_1_y_state = analogRead(j_1_y);
  // Get joystick 1 x val
  j_1_x_state = analogRead(j_1_x);
  // get Joystick 2 button state
  j_2_b_state = digitalRead(j_2_b);
  // Get joystick 2 y val
  j_2_y_state = analogRead(j_2_y);
  // Get joystick 2 x val
  j_2_x_state = analogRead(j_2_x);
}
void updateSensors(){
  updateJoysticks();
  // Get potemtiometer state
  p_state = analogRead(p_pin);
  // Get button 1 state
  b_1_state = digitalRead(b_1_pin);
  // Get button 2 state
  b_2_state = digitalRead(b_2_pin);
}
void updateDataPacket(){
  data.b1 = b_1_state;
  data.b2 = b_2_state;
  data.p = p_state;
  data.j1X = j_1_x_state;
  data.j1Y = j_1_y_state;
  data.j1Switch = j_1_b_state;
  data.j2X = j_2_x_state;
  data.j2Y = j_2_y_state;
  data.j2Switch = j_2_b_state;
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
  time = millis();
  updateSensors();
  updateDataPacket();
  // Transmits every 20 ms;
  radio.write(&data, sizeof(DataPacket));//transmit data
  if(time % 200 == 0){
    printDataPacket();
  }
}