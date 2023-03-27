#include <Adafruit_NeoPixel.h>
#include "drop.h"


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
drop* drip[DROPS];

void setup() {
  Serial.begin(9600);
  strip.begin();
  init_rainbow();

  delay(100);
}

void loop() {
  unsigned long diff;
  static unsigned long last_millis = millis();

  diff = millis() - last_millis;

  drop* current_trip = NULL;
  for (int i = 0; i < DROPS; i += 1) {
    current_trip = drip[i];
    if (current_trip == NULL) {
      boolean led_already_used = false;
      int random_led = 0;
      do {
        led_already_used = false;
        random_led = random(0, LED_COUNT);
        for (int i = 0; i < DROPS; i += 1) {
          if (drip[i] != NULL && random_led == drip[i]->get_number()) {
            led_already_used = true;
            break;
          }
        } 
      } while (led_already_used);

      current_trip = new drop(random(MIN_RAND, MAX_RAND), random_led, &strip);
      drip[i] = current_trip;
    } else {
      if (!current_trip->update(diff)) {
        delete (current_trip);
        drip[i] = NULL;
        current_trip = NULL;
      }
    }
  }
  strip.show();

  last_millis += diff;
}

void init_rainbow() {
  uint16_t hue;
  uint32_t newColor;
  for (int i = 0; i < LED_COUNT; i++) {
    hue = HUEBOT + i * (HUETOP - HUEBOT) / LED_COUNT;
    newColor = strip.gamma32(strip.ColorHSV(hue, SAT, LOWVAL));

    strip.setPixelColor(i, newColor);
    strip.show();
    delay(1);
  }
}
