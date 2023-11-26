#ifndef EFFECT_HPP
#define EFFECT_HPP

class Effect {
public:

  bool enabled;
  bool paused;
  int effect_speed;
  int effect_brightness;

  Effect(void) {
    enabled = false;
  }
  ~Effect(void) {
  }

  virtual void Init();
  virtual void Update();

  // Run when the effect is enabled
  void Enable();
  
  // Run when the effect is paused
  void Pause();

  //Set effect brightness from main brightness
  void SetBrightness(uint8_t main_bright);

  //Get main brightness from effect brightness
  uint8_t GetBrightness(void);

  //Set effect speed from main speed
  void SetSpeed(uint8_t main_speed);

  //Get main speed from effect speed
  uint8_t GetSpeed(void);
};

#endif