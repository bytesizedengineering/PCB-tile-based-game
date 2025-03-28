// Which pin on the Arduino is connected to the NeoPixels?
#define LED_J2_J5 PIN_PB4
#define LED_J3_J4 PIN_PC2
#define LED_J1_J6 PIN_PA7

#define DATA_J1 PIN_PA5

#define RX_J5 PIN_PC5
#define TX_J5 PIN_PC3

//#define DATA_J4 PIN_PC0

#include <tinyNeoPixel.h>
#include <SoftwareSerial.h>

// How many NeoPixels are attached to the microcontroller?
#define NUMPIXELS_J2_J5 6
#define NUMPIXELS_J3_J4 4
#define NUMPIXELS_J1_J6 4

#define RED     0x007F0000
#define GREEN   0x00007F00
#define BLUE    0x0000007F

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
tinyNeoPixel pixels_J2_J5 = tinyNeoPixel(NUMPIXELS_J2_J5, LED_J2_J5, NEO_GRB + NEO_KHZ800);
tinyNeoPixel pixels_J3_J4 = tinyNeoPixel(NUMPIXELS_J3_J4, LED_J3_J4, NEO_GRB + NEO_KHZ800);
tinyNeoPixel pixels_J1_J6 = tinyNeoPixel(NUMPIXELS_J1_J6, LED_J1_J6, NEO_GRB + NEO_KHZ800);

SoftwareSerial mySerial(RX_J5, TX_J5);

void setup() {
  mySerial.begin(4800);
  mySerial.println("Sup Earth");
  pixels_J2_J5.begin(); pixels_J2_J5.clear(); 
  pixels_J3_J4.begin(); pixels_J3_J4.clear(); 
  pixels_J1_J6.begin(); pixels_J1_J6.clear();

  pixels_J2_J5.fill(GREEN);
  pixels_J2_J5.show(); // This sends the updated pixel color to the hardware.

  pinMode(DATA_J1, INPUT_PULLUP);
}

void loop() {
  mySerial.println(digitalRead(DATA_J1));
  if(digitalRead(DATA_J1)){
    pixels_J1_J6.clear(); 
  }
  else{
    pixels_J1_J6.fill(GREEN);
  }
  pixels_J1_J6.show();
  delay(10);
}
