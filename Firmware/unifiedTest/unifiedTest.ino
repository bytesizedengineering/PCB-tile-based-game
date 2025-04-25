#include <tinyNeoPixel.h>

// Uncomment only one of these to select the tile type
//#define TILE_TYPE_AAA
//#define TILE_TYPE_AOA
//#define TILE_TYPE_OOO
#define TILE_TYPE_SOS
//#define TILE_TYPE_SSA


#define RED     0x007F0000
#define GREEN   0x00007F00
#define BLUE    0x0000007F

//enum Color { RED, GREEN, BLUE };

// Structures
struct Connector {
  const char* name;
  uint8_t pin_red;
  uint8_t pin_green;
  uint8_t pin_blue;
};
struct Path {
  int sideA;
  int sideB;
  int ledPin;
  int numLEDs;
  tinyNeoPixel pixelPath;
};
struct Tile {
  Path path1;
  Path path2;
  Path path3;
};

// Global variables
Connector connectors[] = {
  {"", 0, 0, 0},  // Dummy to make indexing start at 1
  {"J1", PIN_PA4, PIN_PA5, PIN_PA6},
  {"J2", PIN_PB7, PIN_PB6, PIN_PB5},
  {"J3", PIN_PB3, PIN_PB2, PIN_PB1},
  {"J4", PIN_PB0, PIN_PC0, PIN_PC1},
  {"J5", PIN_PC3, PIN_PC4, PIN_PC5},
  {"J6", PIN_PA1, PIN_PA2, PIN_PA3},
};

Tile tile;

void setup() {  
  for (int i = 1; i <= 6; i++) {
    pinMode(connectors[i].pin_red, INPUT_PULLUP);
    pinMode(connectors[i].pin_green, INPUT_PULLUP);
    pinMode(connectors[i].pin_blue, INPUT_PULLUP);
  }
  assignTileType();

  tile.path1.pixelPath = tinyNeoPixel(tile.path1.numLEDs, tile.path1.ledPin, NEO_GRB + NEO_KHZ800);
  tile.path2.pixelPath = tinyNeoPixel(tile.path2.numLEDs, tile.path2.ledPin, NEO_GRB + NEO_KHZ800);
  tile.path3.pixelPath = tinyNeoPixel(tile.path3.numLEDs, tile.path3.ledPin, NEO_GRB + NEO_KHZ800);
  
  tile.path1.pixelPath.begin(); tile.path1.pixelPath.clear(); tile.path1.pixelPath.show();
  tile.path2.pixelPath.begin(); tile.path2.pixelPath.clear(); tile.path2.pixelPath.show();
  tile.path3.pixelPath.begin(); tile.path3.pixelPath.clear(); tile.path3.pixelPath.show();

  tile.path1.pixelPath.fill(RED); tile.path1.pixelPath.show();
  tile.path2.pixelPath.fill(GREEN); tile.path2.pixelPath.show();
  tile.path3.pixelPath.fill(BLUE); tile.path3.pixelPath.show();
  delay(1000);
}

void loop() {
  //path 1
  uint32_t colorA = readConnectorColor(connectors[tile.path1.sideA]);
  uint32_t colorB = readConnectorColor(connectors[tile.path1.sideB]);
  if(colorA != 0){
    animatePath(tile.path1.pixelPath, tile.path1.numLEDs, true, colorA);
  }
  else if(colorB != 0){
    animatePath(tile.path1.pixelPath, tile.path1.numLEDs, false, colorB);
  }
  else{
    tile.path1.pixelPath.clear(); tile.path1.pixelPath.show();
  }

  //path 2
  colorA = readConnectorColor(connectors[tile.path2.sideA]);
  colorB = readConnectorColor(connectors[tile.path2.sideB]);
  if(colorA != 0){
    animatePath(tile.path2.pixelPath, tile.path2.numLEDs, true, colorA);
  }
  else if(colorB != 0){
    animatePath(tile.path2.pixelPath, tile.path2.numLEDs, false, colorB);
  }
  else{
    tile.path2.pixelPath.clear(); tile.path2.pixelPath.show();
  }

  //path 3
  colorA = readConnectorColor(connectors[tile.path3.sideA]);
  colorB = readConnectorColor(connectors[tile.path3.sideB]);
  if(colorA != 0){
    animatePath(tile.path3.pixelPath, tile.path3.numLEDs, true, colorA);
  }
  else if(colorB != 0){
    animatePath(tile.path3.pixelPath, tile.path3.numLEDs, false, colorB);
  }
  else{
    tile.path3.pixelPath.clear(); tile.path3.pixelPath.show();
  }
}

void assignTileType(){
  #if defined(TILE_TYPE_AAA)
    tile = {
      {.sideA = 1, .sideB = 6, .ledPin = PIN_PA7, .numLEDs = 4},  // Adjacent J1 ↔ J6
      {.sideA = 2, .sideB = 3, .ledPin = PIN_PB4, .numLEDs = 4},  // Adjacent J2 ↔ J3
      {.sideA = 4, .sideB = 5, .ledPin = PIN_PC2, .numLEDs = 4}   // Adjacent J4 ↔ J5
    };
    #elif defined(TILE_TYPE_AOA)
    tile = {
      {.sideA = 1, .sideB = 6, .ledPin = PIN_PA7, .numLEDs = 4},  // Adjacent J1 ↔ J6
      {.sideA = 2, .sideB = 5, .ledPin = PIN_PB4, .numLEDs = 6},  // Opposite J2 ↔ J5
      {.sideA = 3, .sideB = 4, .ledPin = PIN_PC2, .numLEDs = 4}   // Adjacent J3 ↔ J4
    };
    #elif defined(TILE_TYPE_OOO)
    tile = {
      {.sideA = 1, .sideB = 4, .ledPin = PIN_PB4, .numLEDs = 5},  // Opposite J1 ↔ J4
      {.sideA = 2, .sideB = 5, .ledPin = PIN_PC2, .numLEDs = 6},  // Opposite J2 ↔ J5
      {.sideA = 3, .sideB = 6, .ledPin = PIN_PA7, .numLEDs = 5}   // Opposite J3 ↔ J6
    };
    #elif defined(TILE_TYPE_SOS)
    tile = {
      {.sideA = 1, .sideB = 3, .ledPin = PIN_PA7, .numLEDs = 4},  // Skip     J1 ↔ J3 
      {.sideA = 2, .sideB = 5, .ledPin = PIN_PB4, .numLEDs = 6},  // Opposite J2 ↔ J5
      {.sideA = 6, .sideB = 4, .ledPin = PIN_PC2, .numLEDs = 4}   // Skip     J6 ↔ J4 
    };
    #elif defined(TILE_TYPE_SSA)
    tile = {
      {.sideA = 2, .sideB = 4, .ledPin = PIN_PB4, .numLEDs = 4},  // Skip     J2 ↔ J4  
      {.sideA = 3, .sideB = 5, .ledPin = PIN_PC2, .numLEDs = 5},  // Skip     J3 ↔ J5
      {.sideA = 1, .sideB = 6, .ledPin = PIN_PA7, .numLEDs = 4}   // Adjacent J1 ↔ J6
    };
    #else
    #error "No TILE_TYPE defined!"
  #endif
}

void animatePath(tinyNeoPixel &path, int numLEDs, bool sideAtoSideB, uint32_t color){
  int delayTime = 200;
  path.clear();
  path.show();
  if(sideAtoSideB){
    for (int i = 0; i < numLEDs; i++) {
      path.setPixelColor(i, color);
      path.show();
      delay(delayTime);
    }
  }
  else{
    for (int i = numLEDs-1; i >= 0; i--) {
      path.setPixelColor(i, color);
      path.show();
      delay(delayTime);
    }
  }
  
}

uint32_t readConnectorColor(const Connector& conn) {
  // Read each pin (they're pulled up, so LOW means active)
  bool red   = !digitalRead(conn.pin_red);
  bool green = !digitalRead(conn.pin_green);
  bool blue  = !digitalRead(conn.pin_blue);

  // Pack BGR bits (Red is LSB)
  uint8_t colorBits = (blue << 2) | (green << 1) | red;

  // Convert to 32-bit NeoPixel color (GRB ordering)
  switch (colorBits) {
    case 0b000: return 0x00000000; // Off
    case 0b001: return 0x007F0000; // Red
    case 0b010: return 0x00007F00; // Green
    case 0b011: return 0x007F7F00; // Yellow
    case 0b100: return 0x0000007F; // Blue
    case 0b101: return 0x007F007F; // Magenta
    case 0b110: return 0x00007F7F; // Cyan
    case 0b111: return 0x007F7F7F; // White
    default:    return 0x00000000; // Fallback (Off)
  }
}

