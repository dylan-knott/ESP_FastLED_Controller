/**
 * effect.hpp
 * @brief Defines a standard "effect" object
 *          to be extended when implementing effects
 * @author Dylan Knott
 **/
#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <stdint.h>
#include <FastLED.h>

/**
 * Defines effect interface to access effect implementations
 * Provides Brightness and Speed scaling
**/
class Effect
{
public:

  Effect();

  virtual void Init() = 0;
  virtual void Enable() = 0;
  
  //Calculates a frame of the effect and copies to the given buffer
  virtual void Frame(CRGB *buff, uint16_t BUFF_SIZE) = 0;

  // Set effect brightness from main brightness
  void SetBrightness(uint8_t bright);

  // Set effect speed from main speed
  void SetSpeed(uint8_t speed);

protected:
  uint8_t effect_speed_min;
  uint8_t effect_speed_max;

  uint8_t effect_brightness_min;
  uint8_t effect_brightness_max;
  
  uint8_t effect_speed;
  uint8_t effect_brightness;
};

#endif