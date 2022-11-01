#ifndef __SOLID_ANIMATION_H__
#define __SOLID_ANIMATION_H__

#include "defines.h"
#include "light-animation.h"

class SolidAnimation : public LightAnimation {
 public:
  SolidAnimation(uint8_t *leds_brightness)
      : leds_brightness_(leds_brightness), brightness_(255) {}
  void reset();
  void tick();

 private:
  uint8_t *leds_brightness_;
  uint8_t brightness_;
};

#endif
