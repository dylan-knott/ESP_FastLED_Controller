/**
 * effect.cpp
 * @brief Implements the effect base object
 * @author Dylan Knott
 **/

#include <effect.hpp>
#include <stdint.h>

Effect::Effect()
{
  // Init speed, brightness, mins and maxes
  effect_speed = 0;
  effect_brightness = 0;

  effect_speed_min = 20;
  effect_speed_max = 255;

  effect_brightness_min = 10;
  effect_brightness_max = 255;
}

// Set effect brightness from main brightness
void Effect::SetBrightness(uint8_t bright)
{
  effect_brightness = map8(bright, effect_brightness_min, effect_brightness_max);
}

// Set effect speed from main speed
void Effect::SetSpeed(uint8_t speed)
{
  effect_speed = map8(speed, effect_speed_min, effect_speed_max);
}