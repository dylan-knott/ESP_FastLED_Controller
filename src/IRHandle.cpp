/**
* IRHandle.cpp
* @brief Implementation of IR receiver functions
* @author Dylan Knott
**/

#include <IRHandle.hpp>

namespace IR_REMOTE
{
  using namespace MAIN;

  IRrecv irrecv(IR_RECEIVE_PIN);
  decode_results results;

  void handle_IR(void);

  void init_IR()
  {
    pinMode(IR_RECEIVE_PIN, INPUT);
    irrecv.enableIRIn();
  }

  void loop_IR()
  {
    // Handle IR input if available
    if (irrecv.decode(&results))
    {
      //Run command from recieved code
      if (results.command != 0) { //Filter out Hold codes
        handle_IR();
      }
      //Go back to looking for input
      irrecv.resume();
    }
  }

  void handle_IR()
  {
#ifdef DEBUG_IR
    Serial.print("Code Recv: ");
    Serial.println(results.command);
#endif

    switch ((remote_code_t)(results.command))
    {
    case POWER: // Power button
      if (!power)
      {
        power = true;
        init_lights();
      }
      else
      {
        power = false;
        lights_off();
      }
      break;
    case BRIGHT_UP: // Brightness up
      main_brightness = CLAMP((main_brightness + brightness_button_delta),
                              MIN_BRIGHTNESS, MAX_BRIGHTNESS);
      curr_effect->SetBrightness(main_brightness);
      break;
    case BRIGHT_DOWN: // Brightness down
      main_brightness = CLAMP((main_brightness - brightness_button_delta),
                              MIN_BRIGHTNESS, MAX_BRIGHTNESS);
      curr_effect->SetBrightness(main_brightness);
      break;

    case QUICK: // Speed up
      main_speed += CLAMP((main_speed + speed_button_delta),
                          MIN_SPEED, MAX_SPEED);
      curr_effect->SetSpeed(main_speed);
      break;
    case SLOW: // Speed down
      main_speed += CLAMP((main_speed - speed_button_delta),
                          MIN_SPEED, MAX_SPEED);
      curr_effect->SetSpeed(main_speed);
      break;

    // Modes
    case EFFECT_DIY1: // DIY1: Solid Color
      set_effect(SOLID_COLOR);
      break;

    case EFFECT_DIY2: // DIY2: Pulse
      set_effect(PULSE);
      break;

    case EFFECT_DIY3: // DIY3: Rainbow
      set_effect(RAINBOW);
      break;

    case EFFECT_DIY4: // DIY4:  Stars
      set_effect(STARS);
      break;

    case EFFECT_DIY5: // DIY5:  Twinkle
      set_effect(TWINKLE);
      break;

    case EFFECT_DIY6: // DIY6:  Rainbow Pulse
      set_effect(RAINBOW_PULSE);
      break;

    case EFFECT_AUTO: // Blink
      set_effect(BLINKING);
      break;

    case EFFECT_FADE3: // Breathe
      set_effect(BREATHING);
      break;

    case EFFECT_JUMP3: // Color Jump
      set_effect(COLOR_JUMP);
      break;

    case EFFECT_FADE7: // Rainbow Blink
      set_effect(RAINBOW_BLINK);
      break;

    // Color Presets
    case COLOR_RED: // Red
      set_color(RED);
      break;

    case COLOR_DARK_ORANGE: // Dark Orange
      set_color(DARK_ORANGE);
      break;

    case COLOR_ORANGE: // Orange
      set_color(ORANGE);
      break;

    case COLOR_LIGHT_ORANGE: // Light Orange
      set_color(LIGHT_ORANGE);
      break;

    case COLOR_YELLOW: // Yellow
      set_color(YELLOW);
      break;

    case COLOR_GREEN: // Green
      set_color(GREEN);
      break;

    case COLOR_LIGHT_GREEN: // Light Green
      set_color(LIGHT_GREEN);
      break;

    case COLOR_LIGHT_CYAN: // Light Cyan
      set_color(LIGHT_CYAN);
      break;

    case COLOR_CYAN: // Cyan
      set_color(CYAN);
      break;

    case COLOR_DARK_CYAN: // Dark Cyan
      set_color(DARK_CYAN);
      break;

    case COLOR_BLUE: // Blue
      set_color(BLUE);
      break;

    case COLOR_ROYAL_BLUE: // Royal Blue
      set_color(ROYAL_BLUE);
      break;

    case COLOR_PLUM: // Plum
      set_color(PLUM);
      break;

    case COLOR_VIOLET: // Violet
      set_color(VIOLET);
      break;

    case COLOR_DARK_PINK: // Dark Pink
      set_color(DARK_PINK);
      break;

    case COLOR_WHITE: // White
      set_color(WHITE);
      break;

    case COLOR_WARM_1: // Warm 1
      set_color(WARM_1);
      break;

    case COLOR_WARM_2: // Warm 2
      set_color(WARM_2);
      break;

    case COLOR_COOL_1: // Cool 1
      set_color(COOL_1);
      break;

    case COLOR_COOL_2: // Cool 2
      set_color(COOL_2);
      break;
    }
  }

}
