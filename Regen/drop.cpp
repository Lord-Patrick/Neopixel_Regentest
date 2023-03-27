#include "drop.h"
#include "defs.h"


drop::drop(unsigned long p_counter, int p_num, Adafruit_NeoPixel* p_strip) {
  counter = p_counter;
  counter_max = p_counter;
  num = p_num;
  strip = p_strip;

  // comments are for: noise in the rainbow and below: completely random colors. 
  hue = HUEBOT + p_num * (HUETOP - HUEBOT) / LED_COUNT; // + random(-1024, 1024); 
  //hue = random(HUEBOT, HUETOP);
}

boolean drop::update(unsigned long ms) {
  uint32_t newColor;
  uint16_t brightness = map(counter, counter_max, 0, HIGHVAL, LOWVAL);

  newColor = strip->gamma32(strip->ColorHSV(hue, SAT, brightness));
  strip->setPixelColor(num, newColor);

  if (counter > ms) {
    counter -= ms;
    return true;
  } else {
    return false;
  }
}

int drop::get_number() {
  return num;
}

drop::~drop() {
  /* Set drop to final color: 
  uint32_t newColor;
  uint16_t brightness = LOWVAL;

  newColor = strip->gamma32(strip->ColorHSV(0, 0, brightness));
  strip->setPixelColor(num, newColor);
  */
}
