#include "rain-animation.h"

#include "defines.h"

void RainAnimation::reset() {}

void RainAnimation::tick(const uint16_t palette_frame,
                         const uint16_t pattern_frame) {
  if (this->drops_.size() < this->max_drops_) {
    if (random(100) < percent_chance_to_add_drop_) {
      add_drop();
    }
  }

  // Reset the LED string brightness to re-apply all lights at their current
  // stage
  for (size_t i = 0; i < NUM_LEDS; ++i) {
    leds_brightness_[i] = 0;
  }

  // Loop through the LED chain, apply the lights, and update the stages
  for (List<raindrop>::Iterator it = drops_.begin(); it != drops_.end(); ++it) {
    size_t pos = (*it).position;
    DEBUG("Prossessing position: " + pos);
    DEBUG("Processing stage: " + (*it).stage);
    switch ((*it).stage) {
      case 0:
        leds_brightness_[pos] = 255;
        break;
      case 1:
        if (inside_bounds(pos - 1)) {
          leds_brightness_[pos - 1] = 255;
        }
        leds_brightness_[pos] = 200;
        if (inside_bounds(pos + 1)) {
          leds_brightness_[pos + 1] = 255;
        }
        break;
      case 2:
        if (inside_bounds(pos - 2)) {
          leds_brightness_[pos - 2] = 255;
        }
        if (inside_bounds(pos - 1)) {
          leds_brightness_[pos - 1] = 200;
        }
        leds_brightness_[pos] = 150;
        if (inside_bounds(pos + 1)) {
          leds_brightness_[pos + 1] = 200;
        }
        if (inside_bounds(pos + 2)) {
          leds_brightness_[pos + 2] = 255;
        }
        break;
      case 3:
        if (inside_bounds(pos - 3)) {
          leds_brightness_[pos - 3] = 150;
        }
        if (inside_bounds(pos - 2)) {
          leds_brightness_[pos - 2] = 200;
        }
        if (inside_bounds(pos - 1)) {
          leds_brightness_[pos - 1] = 150;
        }
        leds_brightness_[pos] = 0;
        if (inside_bounds(pos + 1)) {
          leds_brightness_[pos + 1] = 150;
        }
        if (inside_bounds(pos + 2)) {
          leds_brightness_[pos + 2] = 200;
        }
        if (inside_bounds(pos + 3)) {
          leds_brightness_[pos + 3] = 150;
        }
        break;
      case 4:
        if (inside_bounds(pos - 3)) {
          leds_brightness_[pos - 3] = 100;
        }
        if (inside_bounds(pos - 2)) {
          leds_brightness_[pos - 2] = 150;
        }
        if (inside_bounds(pos - 1)) {
          leds_brightness_[pos - 1] = 100;
        }
        leds_brightness_[pos] = 0;
        if (inside_bounds(pos + 1)) {
          leds_brightness_[pos + 1] = 100;
        }
        if (inside_bounds(pos + 2)) {
          leds_brightness_[pos + 2] = 150;
        }
        if (inside_bounds(pos + 3)) {
          leds_brightness_[pos + 3] = 100;
        }
        break;
      case 5:
        if (inside_bounds(pos - 4)) {
          leds_brightness_[pos - 4] = 80;
        }
        if (inside_bounds(pos - 3)) {
          leds_brightness_[pos - 3] = 100;
        }
        if (inside_bounds(pos - 2)) {
          leds_brightness_[pos - 2] = 80;
        }
        if (inside_bounds(pos - 1)) {
          leds_brightness_[pos - 1] = 50;
        }
        leds_brightness_[pos] = 0;
        if (inside_bounds(pos + 1)) {
          leds_brightness_[pos + 1] = 50;
        }
        if (inside_bounds(pos + 2)) {
          leds_brightness_[pos + 2] = 80;
        }
        if (inside_bounds(pos + 3)) {
          leds_brightness_[pos + 3] = 100;
        }
        if (inside_bounds(pos + 4)) {
          leds_brightness_[pos + 4] = 80;
        }
        break;
      case 6:
        if (inside_bounds(pos - 4)) {
          leds_brightness_[pos - 4] = 25;
        }
        if (inside_bounds(pos - 3)) {
          leds_brightness_[pos - 3] = 50;
        }
        if (inside_bounds(pos - 2)) {
          leds_brightness_[pos - 2] = 25;
        }
        if (inside_bounds(pos - 1)) {
          leds_brightness_[pos - 1] = 0;
        }
        leds_brightness_[pos] = 0;
        if (inside_bounds(pos + 1)) {
          leds_brightness_[pos + 1] = 0;
        }
        if (inside_bounds(pos + 2)) {
          leds_brightness_[pos + 2] = 25;
        }
        if (inside_bounds(pos + 3)) {
          leds_brightness_[pos + 3] = 50;
        }
        if (inside_bounds(pos + 4)) {
          leds_brightness_[pos + 4] = 25;
        }
        break;
      case 7:
        if (inside_bounds(pos - 4)) {
          leds_brightness_[pos - 4] = 5;
        }
        if (inside_bounds(pos - 3)) {
          leds_brightness_[pos - 3] = 25;
        }
        if (inside_bounds(pos - 2)) {
          leds_brightness_[pos - 2] = 5;
        }
        if (inside_bounds(pos - 1)) {
          leds_brightness_[pos - 1] = 0;
        }
        leds_brightness_[pos] = 0;
        if (inside_bounds(pos + 1)) {
          leds_brightness_[pos + 1] = 0;
        }
        if (inside_bounds(pos + 2)) {
          leds_brightness_[pos + 2] = 5;
        }
        if (inside_bounds(pos + 3)) {
          leds_brightness_[pos + 3] = 25;
        }
        if (inside_bounds(pos + 4)) {
          leds_brightness_[pos + 4] = 5;
        }
        break;
      case 8:
        if (inside_bounds(pos - 4)) {
          leds_brightness_[pos - 4] = 3;
        }
        if (inside_bounds(pos - 3)) {
          leds_brightness_[pos - 3] = 20;
        }
        if (inside_bounds(pos - 2)) {
          leds_brightness_[pos - 2] = 3;
        }
        if (inside_bounds(pos - 1)) {
          leds_brightness_[pos - 1] = 0;
        }
        leds_brightness_[pos] = 0;
        if (inside_bounds(pos + 1)) {
          leds_brightness_[pos + 1] = 0;
        }
        if (inside_bounds(pos + 2)) {
          leds_brightness_[pos + 2] = 3;
        }
        if (inside_bounds(pos + 3)) {
          leds_brightness_[pos + 3] = 20;
        }
        if (inside_bounds(pos + 4)) {
          leds_brightness_[pos + 4] = 3;
        }
        break;
      case 9:

        break;
    }
    (*it).stage += 1;
  }

  if (drops_.front().stage > 9) {
    drops_.pop_front();
  }

  apply_color_palette(palette_frame);
}

bool RainAnimation::inside_bounds(const size_t pos) const {
  if (pos < NUM_LEDS) {
    return true;
  }
  return false;
}

// Using the defined color palette saved in `current_palette`, starting at
// offset `start_index`, apply the color palette to each pixel on the strip
void RainAnimation::apply_color_palette(const uint8_t palette_frame) {
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

void RainAnimation::add_drop() {
  raindrop new_drop;
  new_drop.position = random(0, NUM_LEDS);
  new_drop.stage = 0;
  drops_.push_back(new_drop);

  DEBUG("Adding drop: " + new_drop.position);
}