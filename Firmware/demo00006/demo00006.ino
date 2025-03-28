// Which pin on the Arduino is connected to the NeoPixels?
#define LED_J2_J5 PIN_PB4
#define LED_J3_J4 PIN_PC2
#define LED_J1_J6 PIN_PA7

#define DATA_J4 PIN_PC0

#include <tinyNeoPixel.h>

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

int delayLength = 500; // delay for half a second

void setup() {
  pixels_J2_J5.begin(); // This initializes the NeoPixel library.
  pixels_J3_J4.begin(); // This initializes the NeoPixel library.
  pixels_J1_J6.begin(); // This initializes the NeoPixel library.

  pixels_J3_J4.fill(GREEN);
  pixels_J3_J4.show(); // This sends the updated pixel color to the hardware.

  pinMode(DATA_J4, OUTPUT);
  digitalWrite(DATA_J4, LOW);
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of NUMPIXELS_J2_J5 minus one.

  
}
