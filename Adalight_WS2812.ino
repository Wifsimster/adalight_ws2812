//////////
//
// Arduino interface for the use of ws2812 operated LEDs
// Uses Adalight protocol and is compatible with Boblight, Prismatik etc
// "Magic Word" for synchronisation is 'Ada' followed by LED High, Low and Checksum
//
//////////

#include "FastLED.h"

// Define the number of LEDs
#define NUM_LEDS 240

// Define SPI Pin
#define PIN 1

// Baudrate, higher rate allows faster refresh rate and more LEDs (defined in /etc/boblight.conf)
#define serialRate 115200

// Utilises FastSPI_LED2
#define FORCE_SOFTWARE_SPI
#define FORCE_SOFTWARE_PINS

// Adalight sends a "Magic Word" (defined in /etc/boblight.conf) before sending the pixel data
uint8_t prefix[] = {'A', 'd', 'a'}, hi, lo, chk, i;

// initialise LED-array
CRGB leds[NUM_LEDS];

void setup()
{
  
  FastLED.addLeds<WS2812, PIN, RGB>(leds, NUM_LEDS);
  
  // initial RGB flash
  LEDS.showColor(CRGB(255, 0, 0));
  delay(500);
  LEDS.showColor(CRGB(0, 255, 0));
  delay(500);
  LEDS.showColor(CRGB(0, 0, 255));
  delay(500);
  LEDS.showColor(CRGB(0, 0, 0));
  
  Serial.begin(serialRate);
  Serial.print("Ada\n"); // Send "Magic Word" string to host
  
}

void loop() { 
  // wait for first byte of Magic Word
  for(i = 0; i < sizeof prefix; ++i) {
    waitLoop: while (!Serial.available()) ;;
    // Check next byte in Magic Word
    if(prefix[i] == Serial.read()) continue;
    // otherwise, start over
    i = 0;
    goto waitLoop;
  }
  
  // Hi, Lo, Checksum
  
  while (!Serial.available()) ;;
  hi=Serial.read();
  while (!Serial.available()) ;;
  lo=Serial.read();
  while (!Serial.available()) ;;
  chk=Serial.read();
  
  // if checksum does not match go back to wait
  if (chk != (hi ^ lo ^ 0x55))
  {
    i=0;
    goto waitLoop;
  }
  
  memset(leds, 0, NUM_LEDS * sizeof(struct CRGB));
  // read the transmission data and set LED values
  for (uint8_t i = 0; i < NUM_LEDS; i++) {
    byte r, g, b;    
    while(!Serial.available());
    r = Serial.read();
    while(!Serial.available());
    g = Serial.read();
    while(!Serial.available());
    b = Serial.read();
    leds[i].r = r;
    leds[i].g = g;
    leds[i].b = b;
  }
  // shows new values
 FastLED.show();
}
