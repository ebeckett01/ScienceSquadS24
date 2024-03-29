// Potentionmeter
  // 5V   |   Grnd
  //    
  //      A2
// Button
//  Grnd  |   4
//  ===========
//  null  |   null
// Joystick
//    Back
// Grnd | 5V | A0 | A1 | 2
//            (Nob)

// Pins
int j_1_y = A1; // Joystick 1 y pin
int j_1_x = A0; // Joystick 1 x pin
int j_1_b = 2;  // Joystick 1 button pin
int j_2_y = A1; // Joystick 2 y pin
int j_2_x = A0; // Joystick 2 x pin
int j_2_b = 2;  // Joystick 2 button pin
int p_pin = A2; // Potentiometer pin
int b_1_pin = 4;// Button 1 pin
int b_2_pin = 4;// Button 2 pin

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

// Time Tracker
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
void printStates(){
    Serial.print("Joystick 1 x:");
    Serial.print(j_1_x_state);
    Serial.print("  y:");
    Serial.print(j_1_y_state);
    Serial.print(" b:");
    Serial.print(j_1_b_state);
    Serial.print("\nJoystick 2 x:");
    Serial.print(j_2_x_state);
    Serial.print("  y:");
    Serial.print(j_2_y_state);
    Serial.print(" b:");
    Serial.print(j_2_b_state);
    Serial.print("\nPotentiometer: ");
    Serial.print(p_state);
    Serial.print("\nButton 1:");
    Serial.print(b_1_state);
    Serial.print("\nButton 2:");
    Serial.println(b_2_state);
}
void loop() {
  // Update time
  time = millis();
  // get new sensor values
  updateSensors();
  // Print States once per second
  if(time % 1000 == 0){
    printStates();
  }
}
