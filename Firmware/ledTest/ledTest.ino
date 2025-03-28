// Which pin on the Arduino is connected to the NeoPixels?
#define LED_J2_J5 PIN_PB4
#define LED_J3_J4 PIN_PC2
#define LED_J1_J6 PIN_PA7

#include <tinyNeoPixel.h>

// How many NeoPixels are attached to the microcontroller?
#define NUMPIXELS_J2_J5 6
#define NUMPIXELS_J3_J4 4
#define NUMPIXELS_J1_J6 4

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
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of NUMPIXELS_J2_J5 minus one.

  for (int i = 0; i < NUMPIXELS_J2_J5; i++) {
    // pixels_J2_J5.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels_J2_J5.setPixelColor(i, pixels_J2_J5.Color(128, 0, 0)); // Moderately bright red color.
    pixels_J2_J5.show(); // This sends the updated pixel color to the hardware.
    delay(delayLength); // Delay for a period of time (in milliseconds).
    pixels_J2_J5.setPixelColor(i, pixels_J2_J5.Color(0, 0, 0));
  }
  pixels_J2_J5.clear(); pixels_J2_J5.show();
  delay(delayLength);
  for (int i = 0; i < NUMPIXELS_J3_J4; i++) {
    // pixels_J3_J4.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels_J3_J4.setPixelColor(i, pixels_J3_J4.Color(0, 128, 0)); // Moderately bright green color.
    pixels_J3_J4.show(); // This sends the updated pixel color to the hardware.
    delay(delayLength); // Delay for a period of time (in milliseconds).
    pixels_J3_J4.setPixelColor(i, pixels_J3_J4.Color(0, 0, 0));
  }
  pixels_J3_J4.clear(); pixels_J3_J4.show();
  delay(delayLength);
  for (int i = 0; i < NUMPIXELS_J1_J6; i++) {
    // pixels_J1_J6.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels_J1_J6.setPixelColor(i, pixels_J1_J6.Color(0, 0, 128)); // Moderately bright blue color.
    pixels_J1_J6.show(); // This sends the updated pixel color to the hardware.
    delay(delayLength); // Delay for a period of time (in milliseconds).
    pixels_J1_J6.setPixelColor(i, pixels_J1_J6.Color(0, 0, 0));
  }
  pixels_J1_J6.clear(); pixels_J1_J6.show();
  delay(delayLength);
}
