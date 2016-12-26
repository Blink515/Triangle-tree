
void rainbowRandomGlitter() {
  fill_rainbow( leds, NUM_LEDS, gHue, rainbowDensity);
  if( random8() < glitterChance ) {  // How often to glitter things up!  Higher number is more often.
    pick = random16(NUM_LEDS);
    if (ledsData[pick][3] == 0 ) {
      ledsData[pick][3] = 40;  // Used to tag pixel and determine glitter time
      ledsData[pick][0] = random8();  // Pick random rgb values
      ledsData[pick][1] = random8();
      ledsData[pick][2] = random8();
    }
  }
  for (uint16_t i=0; i < NUM_LEDS; i++) {
    if (ledsData[i][3] == 0) {
      leds[i].fadeToBlackBy(180);  // Fade down non-glittering pixels so glitter will show up more
    } else {
      //leds[i] = CRGB(ledsData[i][0], ledsData[i][1], ledsData[i][2]);  // Plug in rgb values
      leds[i].fadeToBlackBy(8);  // Slowly fade down
      ledsData[i][0] = leds[i].r;  // Store the rgb values back in ledsData array
      ledsData[i][1] = leds[i].g;
      ledsData[i][2] = leds[i].b;
      ledsData[i][3] = ledsData[i][3] - 1;
    }
  }
}//end rainbowRandomGlitter


//---------------------------------------------------------------
void rainbowShiftedGlitter() {
  fill_rainbow( leds, NUM_LEDS, gHue, rainbowDensity);
  if( random8() < glitterChance ) {  // How often to glitter things up!  Higher number is more often.
    pick = random16(NUM_LEDS);
    if (ledsData[pick][3] == 0 ) {
      ledsData[pick][3] = 35;  // Used to tag pixel and determine glitter time
      CRGB rgb(leds[pick].r, leds[pick].g, leds[pick].b);
      CHSV hsv = rgb2hsv_approximate(rgb);  // Used to get approx Hue
      leds[pick] = CHSV(hsv.hue-50, 255, 255);  // Color shift Hue on glitter pixel
      ledsData[pick][0] = leds[pick].r;  // Store rgb values back in ledsData array
      ledsData[pick][1] = leds[pick].g;
      ledsData[pick][2] = leds[pick].b;
    }
  }
  for (uint16_t i=0; i < NUM_LEDS; i++) {
    if (ledsData[i][3] == 0) {
      leds[i].fadeToBlackBy(180);  // Fade down non-glittering pixels so glitter will show up more
    } else {
      leds[i] = CRGB(ledsData[i][0], ledsData[i][1], ledsData[i][2]);  // Plug in rgb values
      leds[i].fadeToBlackBy(7);  // Slowly fade down
      ledsData[i][0] = leds[i].r;  // Store the rgb values back in ledsData array
      ledsData[i][1] = leds[i].g;
      ledsData[i][2] = leds[i].b;
      ledsData[i][3] = ledsData[i][3] - 1;
    }
  }
}//end rainbowShiftedGlitter

void add_glitter()
{
  int chance_of_glitter =  glitterChance; // percent of the time that we add glitter
  int number_of_glitters = random8(3); // number of glitter sparkles to add
  
  int r = random8(100);
  if( r < chance_of_glitter ) {
    for( int j = 0; j < number_of_glitters; j++) {
      int pos = random16( NUM_LEDS);
      leds[pos] = CRGB::White; // very bright glitter
    }
  }
}

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  EVERY_N_MILLISECONDS_I(timingObj, 1) {
    timingObj.setPeriod(animationSpeed);
    // random colored speckles that blink in and fade smoothly
    leds.fadeToBlackBy(fadeToBlack);
    int pos = random16(NUM_LEDS);
    leds[pos] += CHSV( gHue + random8(64), 240, 255);
    FastLED.show();
  }
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(animationSpeed, 0, NUM_LEDS);
  static int prevpos = 0;
  if( pos < prevpos ) {
    fill_solid( leds+pos, (prevpos-pos)+1, CHSV(gHue,220,255));
  } else {
    fill_solid( leds+prevpos, (pos-prevpos)+1, CHSV( gHue,220,255));
  }
  prevpos = pos;
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t beat = beatsin8( animationSpeed, 64, 255);
  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(currentPalette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}

void juggle()
{
  static uint8_t    numdots =   4; // Number of dots in use.
  static uint8_t   faderate =   2; // How long should the trails be. Very low value = longer trails.
  static uint8_t     hueinc =  255 / numdots - 1; // Incremental change in hue between each dot.
  static uint8_t    thishue =   0; // Starting hue.
  static uint8_t     curhue =   0; // The current hue
  static uint8_t    thissat = 255; // Saturation of the colour.
  static uint8_t thisbright = 255; // How bright should the LED/display be.
  static uint8_t   basebeat =   5; // Higher = faster movement.

  static uint8_t lastSecond =  99;  // Static variable, means it's only defined once. This is our 'debounce' variable.
  uint8_t secondHand = (millis() / 1000) % 30; // IMPORTANT!!! Change '30' to a different value to change duration of the loop.

  if (lastSecond != secondHand) { // Debounce to make sure we're not repeating an assignment.
    lastSecond = secondHand;
    switch (secondHand) {
      case  0: numdots = 1; basebeat = 20; hueinc = 16; faderate = 2; thishue = 0; break; // You can change values here, one at a time , or altogether.
      case 10: numdots = 4; basebeat = 10; hueinc = 16; faderate = 8; thishue = 128; break;
      case 20: numdots = 8; basebeat =  3; hueinc =  0; faderate = 8; thishue = random8(); break; // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
      case 30: break;
    }
  }

  // Several colored dots, weaving in and out of sync with each other
  curhue = thishue; // Reset the hue values.
  fadeToBlackBy(leds, NUM_LEDS, faderate);
  for ( int i = 0; i < numdots; i++) {
    //beat16 is a FastLED 3.1 function
    leds[beatsin16(basebeat + i + numdots, 0, NUM_LEDS)] += CHSV(gHue + curhue, thissat, thisbright);
    curhue += hueinc;
  }
}


// ColorWavesWithPalettes by Mark Kriegsman: https://gist.github.com/kriegsman/8281905786e8b2632aeb
// This function draws color waves with an ever-changing,
// widely-varying set of parameters, using a color palette.
void colorwaves( CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette) 
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
 
  //uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 300, 1500);
  
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5,9);
  uint16_t brightnesstheta16 = sPseudotime;
  
  for( uint16_t i = 0 ; i < numleds; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    uint16_t h16_128 = hue16 >> 7;
    if( h16_128 & 0x100) {
      hue8 = 255 - (h16_128 >> 1);
    } else {
      hue8 = h16_128 >> 1;
    }

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    
    uint8_t index = hue8;
    //index = triwave8( index);
    index = scale8( index, 240);

    CRGB newcolor = ColorFromPalette( palette, index, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (numleds-1) - pixelnumber;

    switch(mapNum) {
      case 1: nblend( ledarray[spiralMap[pixelnumber]], newcolor, 128);
      break;
      case 2: nblend( ledarray[pixelnumber], newcolor, 128);
      break;
      case 3: nblend( ledarray[columnMap[pixelnumber]], newcolor, 128);
      break;
      case 4: nblend( ledarray[chaosMap[pixelnumber]], newcolor, 128);
      break;
      case 5: nblend( ledarray[reverseSpiralMap[pixelnumber]], newcolor, 128);
      break;
      case 6: nblend( ledarray[diamondMap[pixelnumber]], newcolor, 128);
      break;
      default: nblend( ledarray[columnMap[pixelnumber]], newcolor, 128);
      break;
    }
  }
}

// Alternate rendering function just scrolls the current palette 
// across the defined LED strip.
void palettetest( CRGB* ledarray, uint16_t numleds, const CRGBPalette16& gCurrentPalette)
{
  static uint8_t startindex = 0;
  startindex--;
  fill_palette( ledarray, numleds, startindex, (256 / NUM_LEDS) + 1, gCurrentPalette, 255, LINEARBLEND);
}
