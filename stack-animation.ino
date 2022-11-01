#include "defines.h"
#include "stack-animation.h"

void StackAnimation::reset() {}

void StackAnimation::tick() {
  // Check for the base case of no LEDs lit yet
  bool found_lit_led = false;
  bool all_led_lit = true;
  for (size_t i = 0; i < NUM_LEDS; ++i) {
    if (leds_brightness[i]) {
      found_lit_led = true;
    }
    if (!leds_brightness[i]) {
      all_led_lit = false;
    }
  }

  // If no LEDs are lit, then light the first LED and set the direction
  if (!found_lit_led) {
    direction_ = FORWARD;
    leds_brightness[0] = brightness_;
    return;
  }

  // Second base case, if no LEDs are lit, unlight the furthest one and
  // set the direction accordingly.
  if (all_led_lit) {
    direction_ = BACKWARD;
    leds_brightness[NUM_LEDS - 1] = 0;
    return;
  }

  switch (direction_) {
    case FORWARD:
      for (size_t i = 0; i < NUM_LEDS; ++i) {
        // If we've reached the end of the string or if we're right next to
        // another lit LED, then set the initial position and exit
        if (i == NUM_LEDS - 1 ||
            (leds_brightness[i] && leds_brightness[i + 1])) {
          leds_brightness[0] = brightness_;
          break;
        }

        // If our current LED is lit, and the next LED is not lit, then unlight
        // our LED and light the next one.
        if (leds_brightness[i] && !leds_brightness[i + 1]) {
          leds_brightness[i] = 0;
          leds_brightness[i + 1] = brightness_;
          break;
        }
      }
      break;
    case BACKWARD:
      for (size_t i = NUM_LEDS - 1; i >= 0; --i) {
        if (i == NUM_LEDS - 1 && leds_brightness[i]) {
          leds_brightness[i] = 0;
          break;
        }
        if (i == 0 && leds_brightness[i]) {
          leds_brightness[i] = 0;
          break;
        }

        if (i < NUM_LEDS - 1 && leds_brightness[i] && !leds_brightness[i + 1]) {
          leds_brightness[i] = 0;
          leds_brightness[i + 1] = brightness_;
          break;
        }
      }
      break;
  }
}