#ifndef __SOLID_ANIMATION_H__
#define __SOLID_ANIMATION_H__

#include <FastLED.h>

#include "defines.h"
#include "light-animation.h"

class SolidAnimation : public LightAnimation {
 public:
  SolidAnimation(CRGB *leds_, CRGBPalette16 palette, TBlendType blending)
      : LightAnimation(leds_),
        palette_(palette),
        blending_(blending),
        brightness_(255),
        leds_brightness_(new uint8_t[NUM_LEDS]()) {}
  ~SolidAnimation() { delete[] leds_brightness_; }
  void reset();
  void tick(const uint16_t palette_frame, const uint16_t pattern_frame);

 private:
  void apply_color_palette(const uint8_t palette_frame);

  uint8_t *leds_brightness_;
  uint8_t brightness_;
  CRGBPalette16 palette_;
  TBlendType blending_;
};

#endif
