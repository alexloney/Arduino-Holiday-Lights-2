#include "bounce-animation.h"

void BounceAnimation::reset() {}

void BounceAnimation::tick(const uint16_t palette_frame,
                           const uint16_t pattern_frame) {
  DEBUG("Inside Bounce Tick");
  if (direction_ == FORWARD && position_ >= NUM_LEDS - radius_) {
    DEBUG("Switching from Forward to Backward");
    position_ = NUM_LEDS - radius_;
    direction_ = BACKWARD;
  } else if (direction_ == BACKWARD && position_ <= radius_) {
    DEBUG("Switching from Backward to Forward");
    position_ = radius_;
    direction_ = FORWARD;
  }

  DEBUG("Setting brightness to empty");
  for (size_t i = 0; i < NUM_LEDS; ++i) {
    leds_brightness_[i] = 0;
  }

  DEBUG("Setting brightness");
  for (size_t i = position_ - radius_; i <= position_ + radius_; ++i) {
    leds_brightness_[i] = brightness_;
  }

  DEBUG("Updating position");
  switch (direction_) {
    case FORWARD:
      ++position_;
      break;
    case BACKWARD:
      --position_;
      break;
  }

  DEBUG("Updating palette");
  this->apply_color_palette(palette_frame);
}

// Using the defined color palette saved in `current_palette`, starting at
// offset `start_index`, apply the color palette to each pixel on the strip
void BounceAnimation::apply_color_palette(const uint8_t palette_frame) {
  DEBUG("Inside palette update");
  for (size_t i = 0; i < NUM_LEDS; ++i) {
    if (this->leds_brightness_[i] > 0) {
      this->leds_[i] =
          ColorFromPalette(this->palette_, palette_frame + i,
                           this->leds_brightness_[i], this->blending_);
    } else {
      this->leds_[i] = CRGB::Black;
    }
  }
}
