/**
* main.cpp
* @brief Main code module
* @author Dylan Knott
**/

#include <main.hpp>
#include <effect_def.hpp>

namespace MAIN
{
  CRGB leds[NUM_LEDS];

  //Global Vars, Externed in main data
  Effect *effects[NUM_EFFECTS];

  uint8_t main_brightness = INIT_BRIGHTNESS;
  uint8_t main_speed = INIT_SPEED;
  CHSV main_color = color_presets[INIT_COLOR_PRESET];

  //Points to current effect to be processed
  Effect *curr_effect;
  
  //Default effect, to be run at startup
  Effect * const default_effect = effects[SOLID_COLOR];

  bool power = false;

  void set_effect(effect_e effect_enum) {
    FastLED.clear();
    curr_effect = effects[effect_enum];
    curr_effect->Enable();
  }

  void set_color(color_presets_e color) {
    main_color = color_presets[color];
  }

  // Populate effects array
  void init_effects() {
    
      //TESTING
      for (int i = 0; i < NUM_EFFECTS; i++) {
        effects[i] = new EFFECTS::Rainbow();
      }
  }

  // Called when lights should be turned on
  void init_lights()
  {
    curr_effect = default_effect;
  }


  // Called when lights should be turned off
  void lights_off()
  {
    FastLED.clear();
    FastLED.show();
  }
}

//setup and loop must be outside of the MAIN namespace to run with the Arduino OS
void setup()
  {
    // Debug console
    #ifdef SERIAL_DEBUG
    Serial.begin(115200);
    #endif

    //Default to power off
    MAIN::power = false;

    delay(2000);

    //FastLED setup
    FastLED.addLeds<LED_TYPE, FASTLED_DATA_PIN, COLOR_ORDER>(MAIN::leds, NUM_LEDS);
    FastLED.clear();
    FastLED.setMaxPowerInVoltsAndMilliamps(5, mA_MAX);

    MAIN::init_effects();
    IR_REMOTE::init_IR();
  }

  void loop()
  {

    //Faux scheduler using non-blocking waits. Maybe replace with a scheduler lib
    EVERY_N_MILLISECONDS(IR_DELAY_MS)
    {
      IR_REMOTE::loop_IR();
    }

    EVERY_N_MILLISECONDS(PROCESS_DELAY_MS)
    {
      if (MAIN::power) {
        MAIN::curr_effect->Frame(MAIN::leds, NUM_LEDS);
      }
    }

    EVERY_N_MILLISECONDS(DRAW_DELAY_MS)
    {
      if (MAIN::power)
      {
        FastLED.show();
      }
    }

    #ifdef DEBUG_FPS
    EVERY_N_MILLISECONDS(DEBUG_DELAY_MS)
    {
      Serial.print("FPS: ");
      Serial.println(FastLED.getFPS());
    }
    #endif

    yield();
  }
