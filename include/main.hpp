/**
 * main.hpp
 * @brief Main file definitions
 * @author Dylan Knott
 **/

#ifndef MAIN_HPP
#define MAIN_HPP

#include <Arduino.h>
#include <FastLED.h>
#include <IRHandle.hpp>
#include <main_data.hpp>



/*SET UP FASTLED*/
#define FASTLED_INTERNAL
#define LED_TYPE WS2812B    // type of RGB LEDs
#define COLOR_ORDER GRB     // sequence of colors in data stream
#define FASTLED_DATA_PIN 32 // LED data pin

// Time delays
#define IR_DELAY_MS 20
#define PROCESS_DELAY_MS 10
#define DRAW_DELAY_MS 5
#define DEBUG_DELAY_MS 1000

#endif