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

#define LED_J2_J5 PIN_PB4
#define LED_J3_J4 PIN_PC2
#define LED_J1_J6 PIN_PA7

#include <SoftwareSerial.h>
#include <tinyNeoPixel.h>


// define SoftwareSerial objects
SoftwareSerial J1Serial (RX_J1, TX_J1);
SoftwareSerial J2Serial (RX_J2, TX_J2);
SoftwareSerial J3Serial (RX_J3, TX_J3);
SoftwareSerial J4Serial (RX_J4, TX_J4);
SoftwareSerial J5Serial (RX_J5, TX_J5);
SoftwareSerial J6Serial (RX_J6, TX_J6);

// define tinyNeoPixel objects
tinyNeoPixel pixels_J2_J5 = tinyNeoPixel(6, LED_J2_J5, NEO_GRB + NEO_KHZ800);
tinyNeoPixel pixels_J3_J4 = tinyNeoPixel(4, LED_J3_J4, NEO_GRB + NEO_KHZ800);
tinyNeoPixel pixels_J1_J6 = tinyNeoPixel(4, LED_J1_J6, NEO_GRB + NEO_KHZ800);

void setup() {
  // begin all serial instances
  Serial.begin(115200);
  J1Serial.begin(9600);
  J2Serial.begin(9600);
  J3Serial.begin(9600);
  J4Serial.begin(9600);
  J5Serial.begin(9600);
  J6Serial.begin(9600);

  // Initialize all tinyNeoPixel strands.
  pixels_J2_J5.begin(); pixels_J2_J5.clear();
  pixels_J3_J4.begin(); pixels_J3_J4.clear();
  pixels_J1_J6.begin(); pixels_J1_J6.clear();

}

void loop() {
  if (J1Serial.available() >= 3) {    
    byte red = J1Serial.read();
    byte green = J1Serial.read();
    byte blue = J1Serial.read();
    Serial.print("J1Serial received: "); Serial.print(red); Serial.print(green); Serial.println(blue);
    colorWipe("J1", red, green, blue);
  }
  Serial.println("looping");
}

void colorWipe(String side, byte redValue, byte greenValue, byte blueValue){
  if(side == "J1"){
    for (int i = 0; i < 4; i++) {
    pixels_J1_J6.setPixelColor(i, pixels_J1_J6.Color(redValue, greenValue, blueValue)); 
    pixels_J1_J6.show(); // This sends the updated pixel color to the hardware.
    delay(500); // Delay for a period of time (in milliseconds).
  }
  }
}


