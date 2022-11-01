#include "solid-animation.h"

void SolidAnimation::reset() {}

void SolidAnimation::tick() {
  for (size_t i = 0; i < NUM_LEDS; ++i) {
    leds_brightness[i] = brightness_;
  }
}
