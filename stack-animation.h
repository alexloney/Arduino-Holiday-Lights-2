#ifndef __STACK_ANIMATION_H__
#define __STACK_ANIMATION_H__

#include "defines.h"
#include "light-animation.h"

class StackAnimation : public LightAnimation {
 public:
  StackAnimation(uint8_t *leds_brightness)
      : leds_brightness_(leds_brightness),
        direction_(FORWARD),
        brightness_(255) {}
  void reset();
  void tick();

 private:
  uint8_t *leds_brightness_;
  bool direction_;
  uint8_t brightness_;
};

#endif
