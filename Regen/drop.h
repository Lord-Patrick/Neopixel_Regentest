#ifndef DROP_H
#define DROP_H


#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include "defs.h"


class drop {
public:
  drop(unsigned long p_counter, int p_num, Adafruit_NeoPixel* p_strip);
  boolean update(unsigned long  ms); 
  int get_number();
  ~drop();
private:
  Adafruit_NeoPixel* strip;
  uint16_t hue;
  uint16_t br_high;
  uint16_t br_low;
  unsigned long counter;
  unsigned long counter_max;
  int num;
};


#endif