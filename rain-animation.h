#ifndef __STACK_ANIMATION_H__
#define __STACK_ANIMATION_H__

#include "defines.h"
#include "light-animation.h"
#include "list.hpp"

struct raindrop {
  size_t position;
  uint8_t stage;
};

class RainAnimation : public LightAnimation {
 public:
  RainAnimation(CRGB *leds_, CRGBPalette16 palette, TBlendType blending)
      : LightAnimation(leds_),
        palette_(palette),
        blending_(blending),
        brightness_(255),
        leds_brightness_(new uint8_t[NUM_LEDS]()),
        max_drops_(5),
        percent_chance_to_add_drop_(10) {}
  ~RainAnimation() { delete[] leds_brightness_; }
  void reset();
  void tick(const uint16_t palette_frame, const uint16_t pattern_frame);

 private:
  void apply_color_palette(const uint8_t palette_frame);
  void add_drop();
  bool inside_bounds(const size_t pos) const;

  uint8_t *leds_brightness_;
  uint8_t brightness_;
  CRGBPalette16 palette_;
  TBlendType blending_;
  List<raindrop> drops_;
  uint8_t max_drops_;
  uint8_t percent_chance_to_add_drop_;
};

#endif
