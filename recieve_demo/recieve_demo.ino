//same libraries and object creation as your transmitter
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// Create Receiver object
RF24 radio(9, 8);  // CE, CSN
// Data Packet structer must match transceiver
struct DataPacket {
  int jX;
  int jY;
  int jSwitch;
  int nSwitch;
};
DataPacket data;
//address through which two modules communicate.
const byte address[6] = "83287";

void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(0, address);//set receiving to 5-digit address
  radio.startListening();//pretty explicit code call
  //"Sometimes I wish my students had this built-in function" - Prof. Kuska circa 2024
  Serial.begin(9600);
}

void loop() {
  if (radio.available()) {//if a signal is available
    radio.read(&data, sizeof(DataPacket));//read signal being sent
    //the data structure is now here - weeeeeeeeeeeee

    Serial.println(data.jX);
    Serial.println(data.jY);
    Serial.println(data.jSwitch);
    Serial.println(data.nSwitch);
    //we can now use variables in this void loop(). SICK!
    //Serial.println(data.StrHey);//print that variable we created and transmitted
    //what do you think it will print?!

  }
}