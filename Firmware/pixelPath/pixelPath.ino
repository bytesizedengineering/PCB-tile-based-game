#include <tinyNeoPixel.h>

// Uncomment only one of these to select the tile type
//#define TILE_TYPE_AAA
//#define TILE_TYPE_AOA
//#define TILE_TYPE_OOO
//#define TILE_TYPE_SOS
#define TILE_TYPE_SSA

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

  // Runtime animation state
  int animStep = 0;
  bool active = false;
  bool direction = true; // true = sideA → sideB
  uint32_t color = 0;
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
  {"J1", PIN_PA4, PIN_PA5, PIN_PA6},
  {"J2", PIN_PB7, PIN_PB6, PIN_PB5},
  {"J3", PIN_PB3, PIN_PB2, PIN_PB1},
  {"J4", PIN_PB0, PIN_PC0, PIN_PC1},
  {"J5", PIN_PC3, PIN_PC4, PIN_PC5},
  {"J6", PIN_PA1, PIN_PA2, PIN_PA3},
};

Tile tile;
unsigned long lastPathUpdate = 0;

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
  uint32_t colorA = readConnectorColor(connectors[path.sideA]);
  uint32_t colorB = readConnectorColor(connectors[path.sideB]);

  bool sideA_active = (colorA != 0);
  bool sideB_active = (colorB != 0);

  if(sideA_active && !sideB_active) {
    path.direction = true;
    path.color = colorA;
    path.active = true;
    // Mirror to sideB
    setConnectorOutput(connectors[path.sideB], colorA);
    setConnectorInput(connectors[path.sideA]); // Make sure sideA stays input
  }
  else if(sideB_active && !sideA_active) {
    path.direction = false;
    path.color = colorB;
    path.active = true;
    // Mirror to sideA
    setConnectorOutput(connectors[path.sideA], colorB);
    setConnectorInput(connectors[path.sideB]);
  }
  else if (sideA_active && sideB_active) {
    // Optional: prioritize sideB or keep previous direction
    // if (!path.active) {
    //   path.direction = true; // Default choice if both active and not animating
    // }
    // path.color = colorA; // or blend colors, or pick based on logic
    // path.active = true;
  }
  else {
    // Clear path and reset
    path.pixelPath.clear(); path.pixelPath.show();
    path.active = false;
    path.animStep = 0;
    // Set both sides to input
    setConnectorInput(connectors[path.sideA]);
    setConnectorInput(connectors[path.sideB]);
    return;
  }

  if (path.animStep <= path.numLEDs) {
    animatePath(path.pixelPath, path.animStep, path.numLEDs, path.direction, path.color);
    path.animStep++;
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




