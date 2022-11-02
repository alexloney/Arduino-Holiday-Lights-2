#ifndef __BOUNCE_ANIMATION_H__
#define __BOUNCE_ANIMATION_H__

#include "defines.h"
#include "light-animation.h"

class BounceAnimation : public LightAnimation {
 public:
  BounceAnimation(CRGB *leds_, CRGBPalette16 palette, TBlendType blending)
      : LightAnimation(leds_),
        palette_(palette),
        blending_(blending),
        direction_(FORWARD),
        brightness_(255),
        position_(0),
        radius_(2) {
    this->leds_brightness_ = new uint8_t[NUM_LEDS]();
  }
  ~BounceAnimation() { delete[] this->leds_brightness_; }
  void reset();
  void tick(const uint16_t palette_frame, const uint16_t pattern_frame);

 private:
  void apply_color_palette(const uint8_t palette_frame);

  bool direction_;
  uint8_t *leds_brightness_;
  uint8_t brightness_;
  size_t position_;
  uint8_t radius_;
  CRGBPalette16 palette_;
  TBlendType blending_;
};

#endif
