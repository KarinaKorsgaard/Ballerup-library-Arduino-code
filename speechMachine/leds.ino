
#include<FastLED.h>


const uint8_t kMatrixWidth = 12;
const uint8_t kMatrixHeight = 12;
#define MAX_DIMENSION ((kMatrixWidth>kMatrixHeight) ? kMatrixWidth : kMatrixHeight)
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
const bool    kMatrixSerpentineLayout = true;


uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;

  if( kMatrixSerpentineLayout == false) {
    i = (y * kMatrixWidth) + x;
  }

  if( kMatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (kMatrixWidth - 1) - x;
      i = (y * kMatrixWidth) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * kMatrixWidth) + x;
    }
  }

  return i;
}

// The leds
CRGB leds[kMatrixWidth * kMatrixHeight];
CRGB leds2[kMatrixWidth * kMatrixHeight];

static uint16_t x;
static uint16_t y;
static uint16_t z;
uint8_t noise[MAX_DIMENSION][MAX_DIMENSION];

void setupLeds(int numLeds) {
  
  delay(3000);
  LEDS.addLeds<WS2813,14,RGB>(leds,numLeds);
  LEDS.addLeds<WS2813,15,RGB>(leds2,numLeds);
  LEDS.setBrightness(255);

  // Initialize our coordinates to some random values
  x = random16();
  y = random16();
  z = random16();
}

// Fill the x/y array of 8-bit noise values using the inoise8 function.
void fillnoise8(uint16_t speed, uint16_t scale) {
  for(int i = 0; i < MAX_DIMENSION; i++) {
    int ioffset = scale * i;
    for(int j = 0; j < MAX_DIMENSION; j++) {
      int joffset = scale * j;
      noise[i][j] = inoise8(x + ioffset,y + joffset,z);
    }
  }
  z += speed;
}


void updateLeds(uint16_t speed, uint16_t scale, int hue, int saturation) {
  fillnoise8(speed,scale);
  for(int i = 0; i < kMatrixWidth; i++) {
    for(int j = 0; j < kMatrixHeight; j++) {
      leds[XY(i,j)] = CHSV(hue,saturation,noise[i][j]);
      leds2[XY(i,j)] = CHSV(hue,saturation,noise[j][i]);
      // leds[XY(i,j)] = CHSV(hue + (noise[j][i]>>2),saturation,noise[i][j]);
    }
  }
  LEDS.show();
}

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(254); } }


int theled = 0;
static uint8_t wipeHue = 0;
void colorWipe(){
  leds[theled] = CHSV(wipeHue++, 255, 255);
  leds2[theled] = CHSV(wipeHue++, 255, 255);
  FastLED.show(); 
  fadeall();
  theled++;
  if(theled >= NUM_LEDS){
    theled = 0;
  }
}

int blinkValue = 0;
void blinkled(){
  
if(blinkValue > 100) {
  for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i] = CRGB::Red;
    leds2[i] = CRGB::Red;
  }
}else{for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i] = CRGB::Black;
    leds2[i] = CRGB::Black;
  }
  }
  blinkValue++;
  if(blinkValue > 255)blinkValue = 0;
}
