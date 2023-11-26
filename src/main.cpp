#include <main.hpp>


void setup()
{
  // Debug console
  Serial.begin(115200);
  delay(2000);
  
  FastLED.addLeds<LED_TYPE, FASTLED_DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.clear();

  FastLED.setMaxPowerInVoltsAndMilliamps(5, mA_MAX);
  updateBrightness();

  init_IR();
}

void loop()
{
  EVERY_N_MILLISECONDS(IR_DELAY_MS) {
      loop_IR();
      if (effect != lastEffect) {
        lastEffect = effect;
      }
  }

  EVERY_N_MILLISECONDS(PROCESS_DELAY_MS) {

  }

  EVERY_N_MILLISECONDS(DRAW_DELAY_MS) {

  }


#ifdef DEBUG
    EVERY_N_MILLISECONDS(1000) {
      Serial.println("FPS: " + (String)FastLED.getFPS());
    }
#endif
    
  
 if (power){ 
  switch (effect) {
  case 0: //Off
    FastLED.clear();
    break;
  case 1: //Solid Color
    solidFill();
    break;
  case 2: //Pulse
    incrementPulse(false, effectSpeed);
    incrementPulse(false, effectSpeed);
    break;
  case 3: //Rainbow
    rainbow(effectSpeed);
    break;
  case 4: //Stars
    drawStars();
    break;
  case 5: // Rainbow Pulse
    //Still haven't found a suitable effect to go here
    //colorWipe(effectSpeed);
    juggle();
    break;
  case 6: // Twinkle
    //sinelon_RGB(effectSpeed);
    doubleSinelon(RainbowColors_p, effectSpeed);
    break;
  case 7: //Blinking
    blinkEffect();
    break;
  case 8: //Breathing
    breathe();
    break;
  case 9: //Color Jump
    colorJump();
    break;
  case 10: //Rainbow Blink
    rainbowBlink();
    break;
  }

   //Cycle Hue every 25 millis for Comet
   EVERY_N_MILLISECONDS( 5 ) {
    startIndex = startIndex + patternSpeed; /* motion speed */ 

    // slowly cycle the "base color" through the rainbow, used for some patterns
    gHue++;
    gHue2++;
  }
}

  FastLED.show(mainBrightness);
  yield();
}

void SetMainColor()

void incrementPulse(bool reversed, int wait) {
    memcpy(tempPop, popArray, sizeof(popArray));
     for (int i = 0; i < NUM_LEDS; i++) {
      if (reversed){
         popArray[i] = tempPop[i + 1];    
      }
      else {
        if (i == 0) popArray[i] = tempPop[NUM_LEDS-1];
        else popArray[i] = tempPop[i-1];
        }
      }
    for (int a = 0; a < NUM_LEDS; a++){
      if (popArray[a] == 1) {
        leds[a] = mainColor;
      }
      
      if (random(3) < 2) {
        leds[a].fadeToBlackBy(70); //70
      }
    }
    FastLED.delay(map(wait, 1, 50, 0, 70));
  } 

//Called when lights should be turned on
void initializeLights() {
  effect = defaultEffect;
  
  if (effect == 2)
      pulse();
}

//Called when lights should be turned off
void lightsOff() {
  memset(popArray, 0, sizeof(popArray));
  defaultEffect = effect;
  effect = 0;
  FastLED.clear();
  FastLED.show();
}

void updateBrightness() {
  FastLED.setBrightness(mainBrightness);
  FastLED.show();
#ifdef DEBUG
     Serial.println("Main Brightness: " + (String)mainBrightness);
#endif
}

void updateSpeed() {
  effectSpeed =  100 / speedVal;
}


//Light Functions
const int brightnessScale = 15;

void solidFill() {
  
  for (int i = 0; i < NUM_LEDS; i++) {
      uint8_t noiseBright = map(inoise8(i * brightnessScale, millis() / 5), 0, 255, 20, 255);
      leds[i] = CHSV(mainColor.hue, mainColor.s, noiseBright);
    }
}

void blinkEffect() {
  EVERY_N_MILLISECONDS(1000) {
     fill_solid(leds, NUM_LEDS, mainColor);
    }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(25);
    }
  }

void breathe() {
  int beat = beatsin8(25, 1, 255, 0, 0);
  fill_solid(leds, NUM_LEDS, CHSV(mainColor.h, mainColor.s, beat));
  }

void rainbowBlink() {
  int hue = beat8(25,0);
  EVERY_N_MILLISECONDS(480) {
  fill_solid(leds,NUM_LEDS,CHSV(hue, 240, 255));
    }
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(10);
    }
  
  }

void colorJump() {
  int hue = 25.5f * int(beat8(25,0) * 0.0392f);
  fill_solid(leds,NUM_LEDS,CHSV(hue, 240, 255));
  }  

byte saturation = 220;
// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
    int thisSpeed = map(wait, 1, 50, 20, 1);
    uint8_t thisHue = beat8(thisSpeed,255); 
    fill_gradient(leds, 0, CHSV(thisHue, saturation, 255) , NUM_LEDS / 2 - 1, CHSV(thisHue - 1, saturation, 255), LONGEST_HUES);
    fill_gradient(leds, NUM_LEDS / 2 , CHSV(thisHue, saturation, 255) , NUM_LEDS - 1, CHSV(thisHue - 1, saturation, 255), LONGEST_HUES);        
 }


int wipeBPM = 25;
int colorIndex = 0;
void colorWipe(int wait) {
  uint16_t fillNum = map(beat16(wipeBPM, 0), 0,65536, 0, NUM_LEDS - 1);
  if (fillNum < 4) colorIndex = random8();
  
  fill_solid( leds, fillNum, ColorFromPalette(RainbowColors_p, colorIndex));
}


void pulse(){
      FastLED.clear();
      for(int i=0; i < NUM_LEDS; i++){
      int a = i % pulseLength;
      if (a == 0) popArray[i] = 1;
      else popArray[i] = 0;
      yield();
     }
 }

static uint8_t MIN_SAT = 70;
static uint8_t MAX_SAT = 220;
static uint8_t MIN_VAL = 150;
static uint8_t MAX_VAL = 241;

 void drawStars() {
    EVERY_N_MILLISECONDS(effectSpeed * 60) { 
      for (int i = 0; i < 2; i++){
          leds[random(NUM_LEDS)] = CHSV(64, random(MIN_SAT, MAX_SAT), random(MIN_VAL, MAX_VAL));
        }
    }
      blur1d(leds, NUM_LEDS, 50);
  }

void doubleSinelon(CRGBPalette16 palette, int wait)
{
  
    // a colored dot sweeping back and forth, with fading trails
    //Random fading for a twinkle effect
    for (int i = 0; i < NUM_LEDS; i++) {
      if (random(2) < 1) {
        leds[i].fadeToBlackBy(50);
      }
    }
    
    
    pos = beatsin16(5,0,NUM_LEDS-1, 0, 0);
    pos2 = beatsin16(5,0,NUM_LEDS-1, 0 , 32768);
    
    if( pos < prevpos ) { 
      fill_solid( leds+pos, (prevpos-pos)+2, ColorFromPalette(palette, gHue )); //moving back towards 0
    } 
    else { 
      fill_solid( leds+prevpos, (pos-prevpos)+2,  ColorFromPalette(palette, gHue )); //moving towards leds[stripLength]
    }
    prevpos = pos;

    if( pos2 < prevpos2 ) { 
      fill_solid( leds+pos2, (prevpos2-pos2)+2, ColorFromPalette(palette, gHue2 )); //moving back towards 0
    } 
    else { 
      fill_solid( leds+prevpos2, (pos2-prevpos2)+2,  ColorFromPalette(palette, gHue2 )); //moving towards leds[stripLength]
    }
    prevpos2 = pos2;

  
    //Introduce Random Sparkles
    if (random(5) < 1) {
      leds[pos] = leds[pos] + CRGB(90, 90, 90);
      leds[pos+1] = leds[pos+1] + CRGB(90, 90, 90);
      leds[pos+2] = leds[pos+2] + CRGB(90, 90, 90);
      }

    
    if (random(5) < 1) {
      leds[pos2] = leds[pos2] + CRGB(90, 90, 90);
      leds[pos2+1] = leds[pos2+1] + CRGB(90, 90, 90);
      leds[pos2+2] = leds[pos2+2] + CRGB(90, 90, 90);
      }
  
}

void juggle() {
    // eight colored dots, weaving in and out of sync with each other
    for (int i = 0; i < NUM_LEDS; i++) {
        if (random(2) < 1) {
        leds[i].fadeToBlackBy(50);
      }
      }
    byte dothue = 0;
    for( int i = 0; i < 8; i++) {
      int pos = beatsin16( i+2, 1, NUM_LEDS-3 );
      leds[pos] |= CHSV(dothue, 200, 255);
      leds[pos + 1] |= CHSV(dothue, 200, 255);
      leds[pos + 2] |= CHSV(dothue, 200, 255);
      leds[pos + 3] |= CHSV(dothue, 200, 255);
      leds[pos + 4] |= CHSV(dothue, 200, 255);
      leds[pos - 1] |= CHSV(dothue, 200, 255);
      leds[pos - 2] |= CHSV(dothue, 200, 255);
      leds[pos - 3] |= CHSV(dothue, 200, 255);     
      leds[pos - 4] |= CHSV(dothue, 200, 255);     
      dothue += 32;
  }
} 
