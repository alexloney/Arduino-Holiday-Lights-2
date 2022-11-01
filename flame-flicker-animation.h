#ifndef __FLAME_FLICKER_ANIMATION_H__
#define __FLAME_FLICKER_ANIMATION_H__

#include "defines.h"
#include "light-animation.h"

class FlameFlickerAnimation : public LightAnimation {
 public:
  FlameFlickerAnimation(uint8_t *leds_brightness)
      : leds_brightness_(leds_brightness), brightness_(255), tick_index_(0) {}
  void reset();
  void tick();

 private:
  uint8_t *leds_brightness_;
  uint8_t brightness_;
  size_t tick_index_;
};

#endif
