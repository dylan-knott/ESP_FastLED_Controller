/**
* effect_def.hpp
* @brief Contains definitions for all of the light mode effects
* @author Dylan Knott
**/
#include <effect.hpp>
#include <FastLED.h>

namespace EFFECTS {
    
    /*************************Full Strip Effects*************************/
    //SimpleFill - Solid fill with no animation
    class SimpleFill : public Effect {
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    };
    
    //Breathe - Full buffer brightness breathing effect
    class Breathe : public Effect {
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    };

    //RainbowBreathe - Full buffer brightness breathing with 
    //                 a rainbow cycle for color
    class RainbowBreathe : public Effect {
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    };

    //ColorJump - Flips entire buffer through a palette of colors
    class ColorJump : public Effect {
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    };

    //SimpleRainbow - Rainbow effect across the entire buffer
    //                all LEDs are set to the same hue
    class SimpleRainbow : public Effect {
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    };

    /********************************************************************/
    
    
    /*******************Addressable Animation Effects********************/
    //Solid - Solid fill with some noise added to brightness
    class Solid : public Effect {
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    };

    //Rainbow - Hue cycling rainbow effect
    class Rainbow : public Effect {
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    private:
        const static uint8_t RAINBOW_SAT = 220;
    };

    //ColorWipe - Wiping effect, updates color across the RGB buffer
    class ColorWipe : public Effect {
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    };

    //Pulse - Moving pulse effect with comet trail 
    class Pulse : public Effect {
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    };

    //RainbowPulse - Moving pulse effect with comet trail, colors chosen by rainbow palette 
    class RainbowPulse : public Effect {
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    };

    //Stars - Draws stars/twinkles of random color from FG palette over BG color
    class Stars : public Effect {
        Stars(CRGBPalette16 FG_colors, CRGB BG_color);
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    };

    //Double Sinelon - 2 Sine waves with comet tails
    class DoubleSinelon : public Effect {
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    };

    //Juggle - Multiple sine overlayed sine waves
    class Juggle : public Effect {
        void Init();
        void Enable();
        void Frame(CRGB *buff, uint16_t BUFF_SIZE);
    };

}