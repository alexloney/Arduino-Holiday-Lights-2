#include "solid-animation.h"

void SolidAnimation::reset() {}

void SolidAnimation::tick(const uint16_t palette_frame,
                          const uint16_t pattern_frame) {
  for (size_t i = 0; i < NUM_LEDS; ++i) {
    this->leds_brightness_[i] = brightness_;
  }

  this->apply_color_palette(palette_frame);
}

// Using the defined color palette saved in `current_palette`, starting at
// offset `start_index`, apply the color palette to each pixel on the strip
void SolidAnimation::apply_color_palette(const uint8_t palette_frame) {
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