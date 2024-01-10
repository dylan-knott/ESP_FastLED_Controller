/**
* IRHandle.hpp
* @brief Definitions of IR codes and public IR receiver functions
* @author Dylan Knott
**/
#ifndef IR_HANDLE_HPP
#define IR_HANDLE_HPP

#include <main_data.hpp>
#include <stdint.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>

/*SET UP IR RECIEVER*/
#define IR_RECEIVE_PIN 2

// Define remote codes for no-name remote
#define POWER                       64U
#define PAUSE                       65U
#define BRIGHT_UP                   92U
#define BRIGHT_DOWN                 93U
#define QUICK                       23U
#define SLOW                        19U
#define EFFECT_DIY1                 12U
#define EFFECT_DIY2                 13U
#define EFFECT_DIY3                 14U
#define EFFECT_DIY4                 8U
#define EFFECT_DIY5                 9U
#define EFFECT_DIY6                 10U
#define EFFECT_AUTO                 15U
#define EFFECT_FLASH                11U
#define EFFECT_JUMP3                4U
#define EFFECT_JUMP7                5U
#define EFFECT_FADE3                6U
#define EFFECT_FADE7                7U
#define COLOR_RED_UP                20U
#define COLOR_RED_DOWN              16U
#define COLOR_GREEN_UP              21U
#define COLOR_GREEN_DOWN            17U
#define COLOR_BLUE_UP               22U
#define COLOR_BLUE_DOWN             18U
#define COLOR_RED                   88U
#define COLOR_DARK_ORANGE           84U
#define COLOR_ORANGE                80U
#define COLOR_LIGHT_ORANGE          28U
#define COLOR_YELLOW                24U
#define COLOR_GREEN                 89U
#define COLOR_LIGHT_GREEN           85U
#define COLOR_LIGHT_CYAN            81U
#define COLOR_CYAN                  29U
#define COLOR_DARK_CYAN             25U
#define COLOR_BLUE                  69U
#define COLOR_ROYAL_BLUE            73U
#define COLOR_PLUM                  77U
#define COLOR_VIOLET                30U
#define COLOR_DARK_PINK             26U
#define COLOR_WHITE                 68U
#define COLOR_WARM_1                72U
#define COLOR_WARM_2                76U
#define COLOR_COOL_1                31U
#define COLOR_COOL_2                27U


namespace IR_REMOTE {

//Define a type to reference remote codes with correct size
typedef unsigned long remote_code_t;

static const int8_t brightness_button_delta = 10;
static const int8_t speed_button_delta = 10;

/*TODO: Remove if the above solution works
static const long remote_codes[NUM_REMOTE_BUTTONS] = {
    3208707840,
    3191996160,
    2740780800,
    2724069120,
    3893886720,
    3960733440,
    4077715200,
    24061003520,
    4044291840,
    4144561920,
    4127850240,
    4111138560,
    4027580160,
    4094426880,
    4211408640,
    4194696960,
    4177985280,
    4161273600,
    3944021760,
    4010868480,
    3927310080,
    3994156800,
    3910598400,
    3977445120,
    2807627520,
    2874474240,
    2941320960,
    3810328320,
    3877175040,
    2790915840,
    2857762560,
    1465105997,
    3793616640,
    3860463360,
    3125149440,
    3058302720,
    2991456000,
    3776904960,
    3893727949,
    3141861120,
    3075014400,
    3008167680,
    3760193280,
    3827040000
    };
*/

void init_IR(void);
void loop_IR(void);

}

#endif