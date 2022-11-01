#include "bounce-animation.h"

void BounceAnimation::reset() {}

void BounceAnimation::tick() {
  if (direction_ == FORWARD && position_ >= NUM_LEDS - radius_) {
    position_ = NUM_LEDS - radius_;
    direction_ = BACKWARD;
  } else if (direction_ == BACKWARD && position_ <= radius_) {
    position_ = radius_;
    direction_ = FORWARD;
  }

  for (size_t i = 0; i < NUM_LEDS; ++i) {
    leds_brightness[i] = 0;
  }

  for (size_t i = position_ - radius_; i <= position_ + radius_; ++i) {
    leds_brightness[i] = brightness_;
  }

  switch (direction_) {
    case FORWARD:
      ++position_;
      break;
    case BACKWARD:
      --position_;
      break;
  }
}
