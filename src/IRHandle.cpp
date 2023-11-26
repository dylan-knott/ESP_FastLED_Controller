#include <IRHandle.hpp>

void handle_IR(void);

void init_IR(void)
{
  pinMode(IR_RECEIVE_PIN, INPUT);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop_IR(void)
{
  // Handle IR input if available
  if (IrReceiver.decode())
  {
    #ifdef DEBUG
      Serial.println(IrReceiver.decodedIRData.decodedRawData);
    #endif

    handle_IR();

    IrReceiver.resume();
  }
}

void handle_IR()
{
  Serial.println(IrReceiver.decodedIRData.decodedRawData);

  switch ((long)(IrReceiver.decodedIRData.decodedRawData))
  {
  case remote_codes[POWER]: // Power button
    if (!power)
    {
      power = true;
      initializeLights();
    }
    else
    {
      power = false;
      lightsOff();
    }
    break;
  case remote_codes[BRIGHT_UP]: // Brightness up
    mainBrightness = CLAMP((mainBrightness + brightnessButtonDelta), MIN_BRIGHTNESS, MAX_BRIGHTNESS);
    updateBrightness();
    break;
  case remote_codes[BRIGHT_DOWN]: // Brightness down
    mainBrightness = CLAMP((mainBrightness - brightnessButtonDelta), MIN_BRIGHTNESS, MAX_BRIGHTNESS);
    updateBrightness();
    break;

  case remote_codes[QUICK]: // Speed up
    speedVal += speedButtonDelta;
    if (speedVal > 50)
      speedVal = 50;
    updateSpeed();
    break;
  case remote_codes[SLOW]: // Speed down
    speedVal -= speedButtonDelta;
    if (speedVal < 1)
      speedVal = 1;
    updateSpeed();
    break;

  // Modes
  case remote_codes[EFFECT_DIY1]: // DIY1: Solid Color
    FastLED.clear();
    effect = 1;
    break;

  case remote_codes[EFFECT_DIY2]: // DIY2: Pulse
    FastLED.clear();
    pos = 0;
    effect = 2;
    pulse();
    break;

  case remote_codes[EFFECT_DIY3]: // DIY3: Rainbow
    FastLED.clear();
    effect = 3;
    break;

  case remote_codes[EFFECT_DIY4]: // DIY4:  Stars
    FastLED.clear();
    effect = 4;
    break;

  case remote_codes[EFFECT_DIY5]: // DIY5:  Twinkle
    FastLED.clear();
    effect = 6;
    break;

  case remote_codes[EFFECT_DIY6]: // DIY6:  Rainbow Pulse
    FastLED.clear();
    effect = 5;
    break;

  case remote_codes[EFFECT_AUTO]: // Blink
    FastLED.clear();
    effect = 7;
    break;

  case remote_codes[EFFECT_FADE3]: // Breathe
    FastLED.clear();
    effect = 8;
    break;

  case remote_codes[EFFECT_JUMP3]: // Color Jump
    FastLED.clear();
    effect = 9;
    break;

  case remote_codes[EFFECT_FADE7]: // Rainbow Blink
    FastLED.clear();
    effect = 10;
    break;

  // Color Presets
  case remote_codes[COLOR_RED]: // Red
    mainColor = CHSV(HUE_RED, 240, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_DARK_ORANGE]: // Dark Orange
    mainColor = CHSV(20, 240, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_ORANGE]: // Orange
    mainColor = CHSV(HUE_ORANGE, 240, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_LIGHT_ORANGE]: // Light Orange
    mainColor = CHSV(45, 240, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_YELLOW]: // Yellow
    mainColor = CHSV(HUE_YELLOW, 240, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_GREEN]: // Green
    mainColor = CHSV(HUE_GREEN, 240, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_LIGHT_GREEN]: // Light Green
    mainColor = CHSV(HUE_GREEN, 200, 240);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_LIGHT_CYAN]: // Light Cyan
    mainColor = CHSV(110, 240, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_CYAN]: // Cyan
    mainColor = CHSV(HUE_AQUA, 200, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_DARK_CYAN]: // Dark Cyan
    mainColor = CHSV(HUE_AQUA, 240, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_BLUE]: // Blue
    mainColor = CHSV(HUE_BLUE, 240, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_ROYAL_BLUE]: // Royal Blue
    mainColor = CHSV(170, 220, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_PLUM]: // Plum
    mainColor = CHSV(HUE_PURPLE, 240, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_VIOLET]: // Violet
    mainColor = CHSV(205, 240, 255);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_DARK_PINK]: // Dark Pink
    mainColor = CHSV(220, 240, 200);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_WHITE]: // White
    mainColor = CHSV(0, 0, 200);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_WARM_1]: // Warm 1
    mainColor = CHSV(45, 20, 200);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_WARM_2]: // Warm 2
    mainColor = CHSV(45, 40, 200);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_COOL_1]: // Cool 1
    mainColor = CHSV(200, 20, 180);
    if (effect == 3)
      effect = 1;
    break;

  case remote_codes[COLOR_COOL_2]: // Cool 2
    mainColor = CHSV(200, 30, 170);
    if (effect == 3)
      effect = 1;
    break;
  }
}
