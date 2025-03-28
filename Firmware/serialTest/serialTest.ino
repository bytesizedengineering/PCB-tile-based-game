#define RX_J1 PIN_PA6
#define TX_J1 PIN_PA4
#define DATA_J1 PIN_PA5

#define RX_J2 PIN_PB5
#define TX_J2 PIN_PB7
#define DATA_J2 PIN_PB6

#define RX_J3 PIN_PB1
#define TX_J3 PIN_PB3
#define DATA_J3 PIN_PB2

#define RX_J4 PIN_PC1
#define TX_J4 PIN_PB0
#define DATA_J4 PIN_PC0

#define RX_J5 PIN_PC5
#define TX_J5 PIN_PC3
#define DATA_J5 PIN_PC4

#define RX_J6 PIN_PA3
#define TX_J6 PIN_PA1
#define DATA_J6 PIN_PA2

#include <SoftwareSerial.h>


// Set up a new SoftwareSerial object
SoftwareSerial J1Serial (RX_J1, TX_J1);
SoftwareSerial J2Serial (RX_J2, TX_J2);
SoftwareSerial J3Serial (RX_J3, TX_J3);
SoftwareSerial J4Serial (RX_J4, TX_J4);
SoftwareSerial J5Serial (RX_J5, TX_J5);
SoftwareSerial J6Serial (RX_J6, TX_J6);



void setup() {
  J1Serial.begin(9600);
  J2Serial.begin(9600);
  J3Serial.begin(9600);
  J4Serial.begin(9600);
  J5Serial.begin(9600);
  J6Serial.begin(9600);

}

void loop() {
  if (J1Serial.available()) {
    Serial.print("J1Serial says: ");
    Serial.println(J1Serial.readString());
  }
  if (J2Serial.available()) {
    Serial.print("J2Serial says: ");
    Serial.println(J2Serial.readString());
  }
  if (J3Serial.available()) {
    Serial.print("J3Serial says: ");
    Serial.println(J3Serial.readString());
  }
  if (J4Serial.available()) {
    Serial.print("J4Serial says: ");
    Serial.println(J4Serial.readString());
  }
  if (J5Serial.available()) {
    Serial.print("J5Serial says: ");
    Serial.println(J5Serial.readString());
  }
  if (J6Serial.available()) {
    Serial.print("J6Serial says: ");
    Serial.println(J6Serial.readString());
  }
}


