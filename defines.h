#ifndef __DEFINES_H__
#define __DEFINES_H__

// Debug modes are:
// 0 - OFF
// 1 - ALL
// 2 - DEBUG, INFO, WARN, ERROR, FATAL
// 3 - INFO, WARN, ERROR, FATAL
// 4 - WARN, ERROR, FATAL
// 5 - ERROR, FATAL
// 6 - FATAL
#define DEBUG_MODE 0

#if DEBUG_MODE == 0
  #define INIT_DEBUG(X)
  #define INFO(X)
  #define WARN(X)
  #define ERROR(X)
  #define DEBUG(X)
#else
  #define INIT_DEBUG(X) Serial.begin(X)

  #if DEBUG_MODE <= 6
  #define FATAL(X) Serial.println(String("[FATAL] ") + X)
  #else
  #define FATAL(X)
  #endif

  #if DEBUG_MODE <= 5
  #define ERROR(X) Serial.println(String("[ERROR] ") + X)
  #else
  #define ERROR(X)
  #endif

  #if DEBUG_MODE <= 4
  #define WARN(X) Serial.println(String("[WARN] ") + X)
  #else
  #define WARN(X)
  #endif

  #if DEBUG_MODE <= 3
  #define INFO(X) Serial.println(String("[INFO] ") + X)
  #else
  #define INFO(X)
  #endif

  #if DEBUG_MODE <= 2
  #define DEBUG(X) Serial.println(String("[DEBUG] ") + X)
  #else
  #define DEBUG(X)
  #endif

#endif

#define LED_PIN 12
#define NUM_LEDS 50
#define BRIGHTNESS 10
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define UPDATES_PER_SECOND 100

#define FORWARD 0
#define BACKWARD 1

#endif
