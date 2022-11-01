
namespace Settings {
enum Palette {
  RAINBOW,
  PURPLE_PURPLE_ORANGE,
  WHITE,
  RED_WHITE_BLUE_BLACK,
  RED_WHITE_BLUE_BLACK_2,
  RED_WHITE_BLUE_BLACK_3
};

enum Pattern { SOLID, BOUNCE, STACK };

enum Blending { LINEAR_BLEND, NO_BLEND };

class Settings {
 public:
  Settings() {
    this->current_blending_ = LINEARBLEND;
    this->current_palette_ = RainbowColors_p;
    this->current_pattern_ = Pattern::SOLID;
    this->update_palette_speed_ = 1;
    this->update_palette_delay_ = 1;
  }

  void setPalette(String palette) {
    palette.toUpperCase();
    if (palette == "RAINBOW") {
      this->setPalette(Palette::RAINBOW);
    } else if (palette == "PURPLE_PURPLE_ORANGE") {
      this->setPalette(Palette::PURPLE_PURPLE_ORANGE);
    } else if (palette == "WHITE") {
      this->setPalette(Palette::WHITE);
    } else if (palette == "RED_WHITE_BLUE_BLACK") {
      this->setPalette(Palette::RED_WHITE_BLUE_BLACK);
    }
  }
  void setPalette(const Palette palette) {
    switch (palette) {
      case Palette::RAINBOW:
        this->current_palette_ = RainbowColors_p;
        break;
      case Palette::PURPLE_PURPLE_ORANGE:
        this->current_palette_ = CRGBPalette16(
            CRGB::Purple, CRGB::Purple, CRGB::Purple, CRGB::Purple,
            CRGB::Purple, CRGB::Purple, CRGB::Purple, CRGB::Purple,
            CRGB::Orange, CRGB::Orange, CRGB::Orange, CRGB::Orange,
            CRGB::Purple, CRGB::Purple, CRGB::Purple, CRGB::Purple);
        break;
      case Palette::WHITE:
        this->current_palette_ =
            CRGBPalette16(CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray,
                          CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray,
                          CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray,
                          CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray);
        break;
      case Palette::RED_WHITE_BLUE_BLACK:
        this->current_palette_ = CRGBPalette16(
            CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Gray, CRGB::Gray, CRGB::Gray,
            CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Black, CRGB::Black,
            CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::Black);
        break;
    }
  }
  CRGBPalette16 getPalette() { return this->current_palette_; }

  void setBlending(String blending) {
    blending.toUpperCase();
    if (blending == "LINEARBLEND") {
      this->setBlending(Blending::LINEAR_BLEND);
    } else if (blending == "NOBLEND") {
      this->setBlending(Blending::NO_BLEND);
    }
  }
  void setBlending(const Blending blending) {
    switch (blending) {
      case Blending::LINEAR_BLEND:
        this->current_blending_ = LINEARBLEND;
        break;
      case Blending::NO_BLEND:
        this->current_blending_ = NOBLEND;
        break;
    }
  }
  TBlendType getBlending() { return this->current_blending_; }

  void setPattern(String pattern) {
    pattern.toUpperCase();
    if (pattern == "SOLID") {
      this->setPattern(Pattern::SOLID);
    } else if (pattern == "BOUNCE") {
      this->setPattern(Pattern::BOUNCE);
    } else if (pattern == "STACK") {
      this->setPattern(Pattern::STACK);
    }
  }
  void setPattern(const Pattern pattern) { this->current_pattern_ = pattern; }
  Pattern getPattern() { return this->current_pattern_; }

  void setDelay(const uint8_t delay) { this->delay_ = delay; }
  uint8_t getDelay() { return this->delay_; }

  void setUpdatePaletteSpeed(uint8_t update_palette_speed) {
    this->update_palette_speed_ = update_palette_speed;
  }
  uint8_t getUpdatePaletteSpeed() { return this->update_palette_speed_; }

  void setPaletteDelay(uint8_t update_palette_delay) {
    this->update_palette_delay_ = update_palette_delay;
  }
  uint8_t getPaletteDelay() { return this->update_palette_delay_; }

 private:
  CRGBPalette16 current_palette_;
  TBlendType current_blending_;
  Pattern current_pattern_;
  uint8_t delay_;
  uint8_t update_palette_speed_;
  uint8_t update_palette_delay_;
};
}  // namespace Settings
