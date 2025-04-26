#include <tinyNeoPixel.h>

// Uncomment only one of these to select the tile type
//#define TILE_TYPE_AAA
#define TILE_TYPE_AOA
//#define TILE_TYPE_OOO
//#define TILE_TYPE_SOS
//#define TILE_TYPE_SSA

// Structures
struct Connector {
  const char* name; // This stores the PCB connector name J1, J3, etc. 
  uint8_t pin_red; // This stores which MCU pin is connected to pin 2 on the connector
  uint8_t pin_green; // This stores which MCU pin is connected to pin 3 on the connector
  uint8_t pin_blue; // This stores which MCU pin is connected to pin 4 on the connector
};
struct Path {
  int sideA; // This stores which connector is considered side A (J1, J5, etc)
  int sideB; // This stores which connector is considered side B (J1, J5, etc)
  int ledPin; // This stores which MCU pin controls the neopixels
  int numLEDs; // This stores how many neopixels total are in the path
  tinyNeoPixel pixelPath; // neopixel instance 

  // Runtime animation state
  int animStep = 0; // This stores how many pixels are currently lit up during an animation
  bool active = false; // This stores whether or not the path is currently lit up
  bool direction = true; // This stores which side has color data present, also which direction the animation needs to go. True = sideA → sideB
  uint32_t color = 0; // 32 bit color that will be shown on the LEDs when animated
};
struct Tile {
  Path path1;
  Path path2;
  Path path3;

  void begin() {
    path1.pixelPath = tinyNeoPixel(path1.numLEDs, path1.ledPin, NEO_GRB + NEO_KHZ800);
    path2.pixelPath = tinyNeoPixel(path2.numLEDs, path2.ledPin, NEO_GRB + NEO_KHZ800);
    path3.pixelPath = tinyNeoPixel(path3.numLEDs, path3.ledPin, NEO_GRB + NEO_KHZ800);

    path1.pixelPath.begin(); path1.pixelPath.clear(); path1.pixelPath.show();
    path2.pixelPath.begin(); path2.pixelPath.clear(); path2.pixelPath.show();
    path3.pixelPath.begin(); path3.pixelPath.clear(); path3.pixelPath.show();
  }
};

// Global variables
Connector connectors[] = {
  {"", 0, 0, 0},  // Dummy to make indexing start at 1
  {"J1", PIN_PA4, PIN_PA5, PIN_PA6}, // This stores which MCU pin is connected to pins 2,3, and 4 on the connector
  {"J2", PIN_PB7, PIN_PB6, PIN_PB5},
  {"J3", PIN_PB3, PIN_PB2, PIN_PB1},
  {"J4", PIN_PB0, PIN_PC0, PIN_PC1},
  {"J5", PIN_PC3, PIN_PC4, PIN_PC5},
  {"J6", PIN_PA1, PIN_PA2, PIN_PA3},
};

Tile tile; // This is the top level variable to access everything that goes on within the tile
unsigned long lastPathUpdate = 0; // This stores how long it's been since the last time each path was updated

void setup() {  
  for (int i = 1; i <= 6; i++) {
    pinMode(connectors[i].pin_red, INPUT_PULLUP);
    pinMode(connectors[i].pin_green, INPUT_PULLUP);
    pinMode(connectors[i].pin_blue, INPUT_PULLUP);
  }
  assignTileType();

  tile.begin();

  tile.path1.pixelPath.fill(0x007F0000); tile.path1.pixelPath.show();
  tile.path2.pixelPath.fill(0x00007F00); tile.path2.pixelPath.show();
  tile.path3.pixelPath.fill(0x0000007F); tile.path3.pixelPath.show();
  delay(1000);
}

void loop() {  
  if(millis() - lastPathUpdate > 200){
    lastPathUpdate = millis();
    updatePath(tile.path1, connectors);
    updatePath(tile.path2, connectors);
    updatePath(tile.path3, connectors);    
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
      {.sideA = 4, .sideB = 1, .ledPin = PIN_PB4, .numLEDs = 5},  // Opposite J1 ↔ J4
      {.sideA = 5, .sideB = 2, .ledPin = PIN_PC2, .numLEDs = 6},  // Opposite J2 ↔ J5
      {.sideA = 6, .sideB = 3, .ledPin = PIN_PA7, .numLEDs = 5}   // Opposite J3 ↔ J6
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

void animatePath(tinyNeoPixel &path, int animStep, int numLEDs, bool sideAtoSideB, uint32_t color){  
  path.clear();
  //path.show();
  if(sideAtoSideB){
    for (int i = 0; i < animStep && i < numLEDs; i++) {
      path.setPixelColor(i, color);
    }
  }
  else{
    for (int i = numLEDs - 1; i >= numLEDs - animStep && i >= 0; i--) {
      path.setPixelColor(i, color);
    }
  }
  path.show();
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

void updatePath(Path& path, const Connector* connectors) {
  uint32_t colorA = 0;
  uint32_t colorB = 0;

  // Set colorA and colorB, but be careful not to try and read pins that are already set to OUTPUT!!!!
  if (path.active) { // One of the sides has already been set as an OUTPUT so it shouldn't be evaluated for color data
    if (path.direction) { // Side A has color
      colorA = readConnectorColor(connectors[path.sideA]); //Only read the side that is an input, not the side that's an output      
    }
    else { // Side B has color
      colorB = readConnectorColor(connectors[path.sideB]); //Only read the side that is an input, not the side that's an output      
    }
  }
  else { // No active colors detected. It's safe to read both sides
    colorA = readConnectorColor(connectors[path.sideA]); //Only read the side that is an input, not the side that's an output
    colorB = readConnectorColor(connectors[path.sideB]); //Only read the side that is an input, not the side that's an output
  }

  if(colorA && !colorB) {
    path.direction = true; 
    path.color = colorA;    
        
    setConnectorInput(connectors[path.sideA]); // Make sure sideA stays input
    path.active = true;
  }  
  else if(colorB && !colorA) {
    path.direction = false;
    path.color = colorB;        
    setConnectorInput(connectors[path.sideB]);
    path.active = true;
  }
  else if (colorA && colorB) {
    // Need to deal with this condition
    // 
  }
  else { // No color data is present on either side of path
    // Clear path and reset
    path.pixelPath.clear(); path.pixelPath.show();    
    path.animStep = 0;
    // Set both sides to input
    setConnectorInput(connectors[path.sideA]);
    setConnectorInput(connectors[path.sideB]);
    path.active = false;
    return; // no need to evaluate the rest of this function because this path is not active
  }

  if (path.active && path.animStep <= path.numLEDs) { //If the path is active, animate animStep number of LEDs in the direction and color established above
    animatePath(path.pixelPath, path.animStep, path.numLEDs, path.direction, path.color);
    path.animStep++; // Increment the number of LEDs to animate for the next go around
    if (path.animStep > path.numLEDs) {
      // Animation finished, now mirror the color
      if (path.direction) {
        setConnectorOutput(connectors[path.sideB], path.color); // Mirror to sideB
      } else {
        setConnectorOutput(connectors[path.sideA], path.color); // Mirror to sideA
      }
    }
  }
}

void setConnectorOutput(const Connector& conn, uint32_t color) {
  bool red = (color & 0x00FF0000) != 0;
  bool green = (color & 0x0000FF00) != 0;
  bool blue = (color & 0x000000FF) != 0;

  pinMode(conn.pin_red, OUTPUT);
  pinMode(conn.pin_green, OUTPUT);
  pinMode(conn.pin_blue, OUTPUT);

  digitalWrite(conn.pin_red, blue ? LOW : HIGH); // needed to swap blue/red because the PCB was routed to mate tx/rx pairs
  digitalWrite(conn.pin_green, green ? LOW : HIGH);
  digitalWrite(conn.pin_blue, red ? LOW : HIGH); // needed to swap blue/red because the PCB was routed to mate tx/rx pairs
}

void setConnectorInput(const Connector& conn) {
  pinMode(conn.pin_red, INPUT_PULLUP);
  pinMode(conn.pin_green, INPUT_PULLUP);
  pinMode(conn.pin_blue, INPUT_PULLUP);
}




