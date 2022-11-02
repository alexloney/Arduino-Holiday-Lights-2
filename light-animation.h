#ifndef __LIGHT_ANIMATION_H__
#define __LIGHT_ANIMATION_H__

#include <FastLED.h>

class LightAnimation {
 public:
  LightAnimation(CRGB *leds) : leds_(leds) {}
  virtual void reset();
  virtual void tick(const uint16_t palette_frame, const uint16_t pattern_frame);

 protected:
  CRGB *leds_;
};

#endif
