#ifndef __BOUNCE_ANIMATION_H__
#define __BOUNCE_ANIMATION_H__

#include "defines.h"
#include "light-animation.h"

class BounceAnimation : public LightAnimation {
 public:
  BounceAnimation(uint8_t *leds_brightness)
      : leds_brightness_(leds_brightness),
        direction_(FORWARD),
        brightness_(255),
        position_(0),
        radius_(2) {}
  void reset();
  void tick();

 private:
  bool direction_;
  uint8_t *leds_brightness_;
  uint8_t brightness_;
  size_t position_;
  uint8_t radius_;
};

#endif
