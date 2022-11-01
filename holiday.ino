#include <FastLED.h>

#include "bounce-animation.h"
#include "defines.h"
#include "flame-flicker-animation.h"
#include "light-animation.h"
#include "list.hpp"
#include "settings.hpp"
#include "solid-animation.h"
#include "stack-animation.h"

CRGB leds[NUM_LEDS];
uint8_t leds_brightness[NUM_LEDS];

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.

CRGBPalette16 currentPalette;
TBlendType currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

Settings::Settings settings;

LightAnimation *animation = nullptr;

void setup() {
  delay(3000);  // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
      .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  memset(leds_brightness, 0, NUM_LEDS);

  settings.setPalette(Settings::Palette::RAINBOW);
  // settings.setPalette(Settings::Palette::PURPLE_PURPLE_ORANGE);
  // settings.setPalette("red_white_blue_black");
  settings.setBlending(Settings::Blending::LINEAR_BLEND);
  // settings.setBlending(Settings::Blending::NO_BLEND);
  settings.setPattern(Settings::Pattern::STACK);
  settings.setDelay(100);
  settings.setUpdatePaletteSpeed(1);
  settings.setPaletteDelay(1);

  // animation = new StackAnimation(leds_brightness);
  // animation = new BounceAnimation(leds_brightness);
  // animation = new SolidAnimation(leds_brightness);
  animation = new FlameFlickerAnimation(leds_brightness);
}

void loop() {
  uint8_t brightness = 255;

  // ChangePalettePeriodically();

  static uint8_t start_index = 0;
  EVERY_N_MILLISECONDS(settings.getPaletteDelay()) {
    start_index =
        start_index + settings.getUpdatePaletteSpeed(); /* motion speed */
  }

  // wave(startIndex);

  // FillLEDsFromPaletteColors( startIndex);

  // EVERY_N_MILLISECONDS(256) {
  //  twinkle(startIndex, 12);
  //}

  EVERY_N_MILLISECONDS(settings.getDelay()) {
    animation->tick();
    // switch (settings.getPattern()) {
    // case Settings::Pattern::SOLID:
    //   solid(255);
    //   break;
    // case Settings::Pattern::BOUNCE:
    //   bounce(255);
    //   break;
    // case Settings::Pattern::STACK:
    //   stack(255);
    //   break;
    // }

    // smooth_snow(start_index, brightness, 12);
    // solid_wave(255);
    // twinkle_sin_wave(start_index);
    // eyes();
  }

  apply_color_palette(start_index);

  // Push any LED updates to be shown
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

// void colorWipe(CRGB c, int speed, int direction){
//   for(int i=0; i<NUM_LEDS; i++){
//     if(direction == 0){
//       leds[i] = c;
//     }
//     else{
//       leds[NUM_LEDS-1-i] = c;
//     }
//     FastLED.show();
//     delay(speed);
//   }
// }

// Using the defined color palette saved in `current_palette`, starting at
// offset `start_index`, apply the color palette to each pixel on the strip
void apply_color_palette(const uint8_t &start_index) {
  for (size_t i = 0; i < NUM_LEDS; ++i) {
    if (leds_brightness[i] > 0) {
      leds[i] = ColorFromPalette(settings.getPalette(), start_index + i,
                                 leds_brightness[i], settings.getBlending());
    } else {
      leds[i] = CRGB::Black;
    }
  }
}

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