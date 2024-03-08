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

// Constants
// Joystick 1
int j_1_y = A1; // Joystick 1 y
int j_1_y_state = 0; // Joystick 1 y state
int j_1_x = A0; // Joystick 1 x
int j_1_x_state = 0; // Joystick 1 x state
int j_1_b = 2;  // Joystick 1 button
int j_1_b_state = 0; // Joystcik 1 button state

// Potentiometer
int p_pin = A2;
int p_state = 0;

// Button
int b_1_pin = 4;
int b_1_state = 0;


// Time Tracker
unsigned long time;
void setup() {
  // Joystick Setup
  pinMode(j_1_y, INPUT);
  pinMode(j_1_x, INPUT);
  pinMode(j_1_b, INPUT_PULLUP);
  // Potentiomete Setup
  pinMode(p_pin, INPUT); 
  // Button Setup
  pinMode(b_1_pin, INPUT_PULLUP);
  // Serial Communication
  Serial.begin(9600);

}

void loop() {
  // Update time
  time = millis();
  // get Joystick button state
  j_1_b_state = digitalRead(j_1_b);
  // Get joystick y val
  j_1_y_state = analogRead(j_1_y);
  // Get joystick x val
  j_1_x_state = analogRead(j_1_x);
  
  // Get potemtiometer state
  p_state = analogRead(p_pin);

  // Get button state
  b_1_state = digitalRead(b_1_pin);

  // Print States once per second
  if(time % 1000 == 0){
    Serial.print("Joystick x:");
    Serial.print(j_1_x_state);
    Serial.print("  y:");
    Serial.print(j_1_y_state);
    Serial.print(" b:");
    Serial.print(j_1_b_state);
    Serial.print("\nPotentiometer: ");
    Serial.print(p_state);
    Serial.print("\nButton:");
    Serial.println(b_1_state);
  }
}
