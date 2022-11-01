#include "flame-flicker-animation.h"

void FlameFlickerAnimation::reset() {}

void FlameFlickerAnimation::tick() {
  for (size_t i = 0; i < NUM_LEDS; ++i) {
    leds_brightness[i] = (int)(sin(tick_index_) * 255);
  }
  ++tick_index_;
}
