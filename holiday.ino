#include <FastLED.h>

#include "bounce-animation.h"
#include "defines.h"
#include "light-animation.h"
#include "rain-animation.h"
#include "settings.hpp"
// #include "flame-flicker-animation.h"
// #include "solid-animation.h"
#include "stack-animation.h"
// #include "lightning-animation.h"

// uint8_t leds_brightness[NUM_LEDS];

// CRGBPalette16 currentPalette;
// TBlendType currentBlending;

// extern CRGBPalette16 myRedWhiteBluePalette;
// extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

CRGB leds[NUM_LEDS];
Settings::Settings settings;
LightAnimation *animation = nullptr;

void setup() {
  delay(3000);

  INIT_DEBUG(115200);

  // Setup the FastLED library
  DEBUG("Initializing FastLED Library");
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
      .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);

  // TEST CODE: Apply default settings
  DEBUG("Initializing test settings");
  settings.setPalette(Settings::Palette::RAINBOW);
  // settings.setPalette(Settings::Palette::PURPLE_PURPLE_ORANGE);
  // settings.setPalette("red_white_blue_black");
  settings.setBlending(Settings::Blending::LINEAR_BLEND);
  // settings.setBlending(Settings::Blending::NO_BLEND);
  settings.setPattern(Settings::Pattern::STACK);
  settings.setDelay(100);
  settings.setUpdatePaletteSpeed(1);
  settings.setPaletteDelay(1);

  DEBUG("Initializing animations library");
  // animation = new StackAnimation(leds, settings.getPalette(),
  // settings.getBlending());
  animation =
      new RainAnimation(leds, settings.getPalette(), settings.getBlending());
  // animation = new SolidAnimation(leds_brightness);
  // animation = new FlameFlickerAnimation(leds_brightness);
  // animation = new BounceAnimation(leds, settings.getPalette(),
  // settings.getBlending());
}

void loop() {
  static uint16_t palette_index = 0;
  static uint16_t frame = 0;

  // DEBUG("Main loop " + frame);

  // Determine the speed at which the palette will flow through
  // the animation, controlled by a palette speed (large increment)
  // and a palette delay (small increment).
  EVERY_N_MILLISECONDS(settings.getPaletteDelay()) {
    palette_index += settings.getUpdatePaletteSpeed();
  }

  EVERY_N_MILLISECONDS(settings.getDelay()) {
    // DEBUG("Ticking animation");
    animation->tick(palette_index, frame);
    // DEBUG("Completed animation tick");
    ++frame;
  }

  // Push any LED updates to be shown
  // DEBUG("Showing LEDs");
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
  // DEBUG("Exiting main loop");
}

/*

// Apply a random brightness to each individual light on the strip
void twinkle_wave(const uint8_t &min_brightness,
                  const uint8_t &max_brightness) {
  for (size_t i = 0; i < NUM_LEDS; ++i) {
    leds_brightness[i] = random(min_brightness, max_brightness);
  }
}

// Provides a sliding wave across the LEDs
void twinkle_sin_wave(const unsigned int &index) {
  for (size_t i = 0; i < NUM_LEDS; ++i) {
    leds_brightness[i] = (int)(sin(index + i) * 255);
  }
}

// This is a non-blocking function to create a snowfall-like effect by picking
// random LEDs and lighting them up according to the current color palette.
// Once a maximum number of LEDs is reached, denoted by the `max_count`
// variable, the LEDs will be reset back to blank to start over. One thing to
// note about this is that the amount set does not account for overlap with
// the LEDs, so if the same pixel is randomly chosen twice, it will count
// twice even though no additional lights are lit up.
//
// This function is non-blocking, allowing it to be executed and timed from
// the main loop without using delay() to prevent other processing.
void snow(uint8_t idx, uint8_t brightness, uint8_t max_count) {
  static uint8_t amount_set = 0;

  if (amount_set >= max_count) {
    for (int i = 0; i < NUM_LEDS; ++i) {
      leds_brightness[i] = 0;
    }
    amount_set = 0;
  }

  leds_brightness[random(NUM_LEDS)] = brightness;
  ++amount_set;
}

void smooth_snow(uint8_t idx, uint8_t brightness, uint8_t max_count) {
  static List<unsigned int> lights;
  static uint8_t direction = 1;

  if (lights.size() >= max_count && direction == 1) {
    direction = 0;
  } else if (lights.size() == 0 && direction == 0) {
    direction = 1;
  }

  switch (direction) {
    case 0:
      if (lights.size() > 0) {
        leds_brightness[lights.pop_front()] = 0;
      }
      break;
    case 1:
      unsigned int next_light = random(NUM_LEDS);
      lights.insert(next_light);
      // leds[next_light] = ColorFromPalette(currentPalette, idx, brightness,
      // currentBlending);
      leds_brightness[next_light] = brightness;
      break;
  }
}

void eyes() {
  static size_t position = 0;
  static bool direction = 1;
  static uint8_t stage = 0;

  if (stage == 0) {
    direction = 1;
    stage = 1;
    position = random(5, NUM_LEDS - 5);
    memset(leds_brightness, 0, sizeof(leds_brightness));
  }

  if (stage >= 17) {
    direction = 0;
  }

  leds_brightness[position - 3] = leds_brightness[position + 3] = stage * 15;
  leds_brightness[position - 4] = leds_brightness[position - 2] =
      leds_brightness[position + 2] = leds_brightness[position + 4] = stage * 5;

  switch (direction) {
    case 0:
      --stage;
      break;
    case 1:
      ++stage;
      break;
  }
}

void FillLEDsFromPaletteColors(uint8_t colorIndex) {
  uint8_t brightness = 255;

  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness,
                               currentBlending);
    colorIndex += 3;
  }
}

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p,
// RainbowStripeColors_p, OceanColors_p, CloudColors_p, LavaColors_p,
// ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can
// write code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically() {
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;

  if (lastSecond != secondHand) {
    lastSecond = secondHand;
    if (secondHand == 0) {
      currentPalette = RainbowColors_p;
      currentBlending = LINEARBLEND;
    }
    if (secondHand == 10) {
      currentPalette = RainbowStripeColors_p;
      currentBlending = NOBLEND;
    }
    if (secondHand == 15) {
      currentPalette = RainbowStripeColors_p;
      currentBlending = LINEARBLEND;
    }
    if (secondHand == 20) {
      SetupPurpleAndGreenPalette();
      currentBlending = LINEARBLEND;
    }
    if (secondHand == 25) {
      SetupTotallyRandomPalette();
      currentBlending = LINEARBLEND;
    }
    if (secondHand == 30) {
      SetupBlackAndWhiteStripedPalette();
      currentBlending = NOBLEND;
    }
    if (secondHand == 35) {
      SetupBlackAndWhiteStripedPalette();
      currentBlending = LINEARBLEND;
    }
    if (secondHand == 40) {
      currentPalette = CloudColors_p;
      currentBlending = LINEARBLEND;
    }
    if (secondHand == 45) {
      currentPalette = PartyColors_p;
      currentBlending = LINEARBLEND;
    }
    if (secondHand == 50) {
      currentPalette = myRedWhiteBluePalette_p;
      currentBlending = NOBLEND;
    }
    if (secondHand == 55) {
      currentPalette = myRedWhiteBluePalette_p;
      currentBlending = LINEARBLEND;
    }
  }
}

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette() {
  for (int i = 0; i < 16; ++i) {
    currentPalette[i] = CHSV(random8(), 255, random8());
  }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette() {
  // 'black out' all 16 palette entries...
  fill_solid(currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;
}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette() {
  CRGB purple = CHSV(HUE_PURPLE, 255, 255);
  CRGB green = CHSV(HUE_GREEN, 255, 255);
  CRGB black = CRGB::Black;

  currentPalette =
      CRGBPalette16(green, green, black, black, purple, purple, black, black,
                    green, green, black, black, purple, purple, black, black);
}

// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM = {
    CRGB::Red,
    CRGB::Gray,  // 'white' is too bright compared to red and blue
    CRGB::Blue, CRGB::Black,

    CRGB::Red,  CRGB::Gray,  CRGB::Blue,  CRGB::Black,

    CRGB::Red,  CRGB::Red,   CRGB::Gray,  CRGB::Gray,
    CRGB::Blue, CRGB::Blue,  CRGB::Black, CRGB::Black};
*/

// Additional notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes.
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.