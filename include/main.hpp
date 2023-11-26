#ifndef MAIN_HPP
#define MAIN_HPP

#include <Arduino.h>
#include <effect.hpp>
#include <FastLED.h>
#include <IRHandle.hpp>
#include <main_data.hpp>

#define DEBUG

#define HOME

/*SET UP FASTLED*/
#define FASTLED_INTERNAL
#define LED_TYPE WS2812B    // type of RGB LEDs
#define COLOR_ORDER GRB     // sequence of colors in data stream
#define FASTLED_DATA_PIN 32 // LED data pin

#ifdef APARTMENT
#define NUM_LEDS 739 // 450 LEDs numbered [0..449] (APARTMENT)
#define mA_MAX 100000
#endif
#ifdef HOME
#define NUM_LEDS 450 // 450 LEDs numbered [0..449] (HOME)
#define mA_MAX 20000
#endif


//Main brightness and speed consts
#define MAX_BRIGHTNESS 255 // absolute maximum main brightness value
#define MIN_BRIGHTNESS 20  // absolute minimum main brightness value
#define INIT_BRIGHTNESS 80 // initial main brightness value

#define MAX_SPEED 255 //absolute maximum main speed value
#define MIN_SPEED 20 //absolute minimum main speed value
#define INIT_SPEED 100 //initial main speed value


//Time delays
#define IR_DELAY_MS 70
#define PROCESS_DELAY_MS 10
#define DRAW_DELAY_MS 5

/*UTILITY MACROS*/
#define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
#define TIMES_PER_SECOND(x) EVERY_N_MILLISECONDS(1000 / x)
#define CLAMP(x, n, m) ((x > m) ? m : (x < n) ? n : x)

bool power;

CHSV mainColor = CHSV(200, 240, 230);
CRGB leds[NUM_LEDS];

main_vals_t main_vals;

uint8_t effect;
uint8_t defaultEffect;

uint8_t effectSpeed;

uint8_t pulseLength;
uint16_t popArray[NUM_LEDS];
uint16_t tempPop[NUM_LEDS];
uint8_t lastEffect;
uint16_t gHue; // rotating "base color" used by many of the patterns
uint16_t gHue2;
uint16_t startIndex;
uint8_t patternSpeed; // TODO: Turn this into a "mainSpeed" to be manipulated by individual patterns
uint8_t patternAdj;
uint16_t pos; // TODO: See where these are used and get rid of them?
uint16_t prevpos;
uint16_t pos2;
uint16_t prevpos2;

enum light_mode_e
{
  OFF,
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

CHSV color_presets[NUM_COLOR_PRESETS] = {
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

Effect *effects[NUM_EFFECTS];

void incrementPulse(bool reversed, int wait);
void initializeLights();
void lightsOff();
void updateBrightness();
void updateSpeed();

void solidFill();
void blinkEffect();
void breathe();
void rainbowBlink();
void colorJump();
void rainbow(int wait);
void colorWipe(int wait);
void pulse();
void drawStars();
void doubleSinelon(CRGBPalette16 palette, int wait);
void juggle();

#endif