/**
 * main_data.hpp
 * @brief Public definitions for the main file
 * @author Dylan Knott
 **/

#ifndef MAIN_DATA_HPP
#define MAIN_DATA_HPP

#include <stdint.h>
#include <effect.hpp>
#include <FastLED.h>

//Uncomment to debug the program
#define DEBUG_IR
//#define DEBUG_FPS


//Config which lighting environment is being used
#define HOME

#ifdef APARTMENT
#define NUM_LEDS 739 // 739 LEDs numbered [0..738] (APARTMENT)
#define mA_MAX 100000
#endif
#ifdef HOME
#define NUM_LEDS 450 // 450 LEDs numbered [0..449] (HOME)
#define mA_MAX 20000
#endif


#if defined(DEBUG_IR) || defined(DEBUG_FPS) 
#define SERIAL_DEBUG
#else
#undef SERIAL_DEBUG
#endif

// Main brightness and speed consts
#define MAX_BRIGHTNESS 255 // absolute maximum main brightness value
#define MIN_BRIGHTNESS 20  // absolute minimum main brightness value
#define INIT_BRIGHTNESS 80 // initial main brightness value

//Speed defined as cycles per minute
#define MAX_SPEED 255  // absolute maximum main speed value
#define MIN_SPEED 20   // absolute minimum main speed value
#define INIT_SPEED 100 // initial main speed value


/*UTILITY MACROS*/
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#define TIMES_PER_SECOND(x) EVERY_N_MILLISECONDS(1000 / (x))
#define CLAMP(x, n, m) (((x) > (m)) ? (m) : ((x) < (n)) ? (n) \
                                              : (x))

namespace MAIN
{

  // Color definitions using enum,
  // parallel to the color_presets array below, which defines the CHSV values
  enum color_presets_e
  {
    RED,
    DARK_ORANGE,
    ORANGE,
    LIGHT_ORANGE,
    YELLOW,
    GREEN,
    LIGHT_GREEN,
    LIGHT_CYAN,
    CYAN,
    DARK_CYAN,
    BLUE,
    ROYAL_BLUE,
    PLUM,
    VIOLET,
    DARK_PINK,
    WHITE,
    WARM_1,
    WARM_2,
    COOL_1,
    COOL_2,
    NUM_COLOR_PRESETS
  };

  #define INIT_COLOR_PRESET RED

  const CHSV color_presets[NUM_COLOR_PRESETS] = {
      CHSV(HUE_RED, 240, 255),
      CHSV(20, 240, 255),
      CHSV(HUE_ORANGE, 240, 255),
      CHSV(45, 240, 255),
      CHSV(HUE_YELLOW, 240, 255),
      CHSV(HUE_GREEN, 240, 255),
      CHSV(HUE_GREEN, 200, 240),
      CHSV(110, 240, 255),
      CHSV(HUE_AQUA, 200, 255),
      CHSV(HUE_AQUA, 240, 255),
      CHSV(HUE_BLUE, 240, 255),
      CHSV(170, 220, 255),
      CHSV(HUE_PURPLE, 240, 255),
      CHSV(205, 240, 255),
      CHSV(220, 240, 200),
      CHSV(0, 0, 200),
      CHSV(45, 20, 200),
      CHSV(45, 40, 200),
      CHSV(200, 20, 180),
      CHSV(200, 30, 170)};

  //Enumerate possible effects, used to index the effects array
  enum effect_e
  {
    SOLID_COLOR,
    PULSE,
    RAINBOW,
    STARS,
    RAINBOW_PULSE,
    TWINKLE,
    BLINKING,
    BREATHING,
    COLOR_JUMP,
    RAINBOW_BLINK,
    COLOR_FILL,
    NUM_EFFECTS
  };
  
  extern CRGB leds[NUM_LEDS];
  extern Effect *effects[NUM_EFFECTS];

  extern uint8_t main_brightness;
  extern uint8_t main_speed;
  extern CHSV main_color;

  //Points to current effect to be processed
  extern Effect *curr_effect;

  //Default effect, to be run at startup
  extern Effect * const default_effect;

  extern bool power;

  //Helper function definitions
  void init_effects(void);
  void init_lights(void);
  void lights_off(void);

  void set_effect(effect_e effect);
  void set_color(color_presets_e color);

}

#endif