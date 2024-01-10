/**
 * effect_rainbow.cpp
 * @brief Contains the implementation for a light effect
 * @author Dylan Knott
 **/

#include <effect_def.hpp>
namespace EFFECTS
{
    void Rainbow::Init()
    {
    }

    void Rainbow::Enable() {}

    void Rainbow::Frame(CRGB *buff, uint16_t BUFF_SIZE)
    {
        // Takes BPM in beats per minute (rainbow cycles per minute in this case)
        uint8_t startHue = beat8(effect_speed, 255);
        fill_gradient(buff, 0, CHSV(startHue, RAINBOW_SAT, 255), BUFF_SIZE / 2 - 1,
                      CHSV(startHue - 1, RAINBOW_SAT, 255), LONGEST_HUES);
        fill_gradient(buff, BUFF_SIZE / 2, CHSV(startHue, RAINBOW_SAT, 255), BUFF_SIZE - 1,
                      CHSV(startHue - 1, RAINBOW_SAT, 255), LONGEST_HUES);
    }
}