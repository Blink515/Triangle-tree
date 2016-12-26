uint8_t spiralMap[] =
{
  0, 1, 2, 3, 4, 12, 18, 22, 24, 21, 16, 9, 8, 7, 6, 5, 13, 19, 23, 20, 15, 10, 11, 17, 14
};

uint8_t columnMap[] =
{
  2, 14, 17, 23, 24, 7, 6, 10, 11, 20, 19, 21, 22, 1, 3, 15, 13, 16, 18, 8, 5, 9, 12, 0, 4
};

uint8_t chaosMap[] =
{
  0, 4, 24, 1, 12, 21, 2, 18, 16, 3, 22, 9, 8, 5, 23, 7, 13, 20, 6, 19, 15, 10, 11, 17, 14
};

uint8_t reverseSpiralMap[] =
{
  14, 17, 11, 10, 15, 20, 23, 19, 13, 5, 6, 7, 8, 9, 16, 21, 24, 22, 18, 12, 4, 3, 2, 1, 0
};

uint8_t diamondMap[] =
{
  9, 8, 10, 7, 11, 6, 12, 5, 16, 15, 17, 14, 18, 13, 21, 20, 22, 19, 24, 23, 0, 1, 2, 3, 4
};

void spiral() {
  static int i = 0;

  leds.fadeToBlackBy(fadeToBlack);
  if (i >= NUM_LEDS) {
    i = 0;
  }
  EVERY_N_MILLISECONDS_I(timingObj, 15) {
    timingObj.setPeriod(animationSpeed);
    leds[spiralMap[i]] = CHSV(gHue, 255, 255);
    i++;
  }
}

void spiralPalette() {
  static uint8_t paletteIndex = 0;
  static int i = 0;

  leds.fadeToBlackBy(fadeToBlack);
  if (i >= NUM_LEDS) {
    i = 0;
  }
  if (paletteIndex > 255) {
    paletteIndex = 0;
  }
  EVERY_N_MILLISECONDS_I(timingObj, 15) {
    timingObj.setPeriod(animationSpeed);
    leds.fadeToBlackBy(fadeToBlack);
    leds[spiralMap[i]] = ColorFromPalette( currentPalette, paletteIndex, 255);
    i++;
    paletteIndex += 16;
  }
}

void fillUp() {
  static uint8_t paletteIndex = 0;
  static uint8_t level = 1;

  if (level > 6) {
    level = 1;
  }
  if (paletteIndex > 255) {
    paletteIndex = 0;
  }
  switch (level) {
    case 1: leds(0, 8) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 2: leds(9, 15) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 3: leds(16, 20) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 4: leds(21, 23) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 5: leds[24] = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 6: leds(0, NUM_LEDS - 1) = CRGB::Black;
      break;
    default: leds(0, NUM_LEDS - 1) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
  }

  EVERY_N_MILLISECONDS_I(timingObj, 200) {
    timingObj.setPeriod(animationSpeed);
    level++;
    paletteIndex += 16;
  }
}

void fillDown() {
  static uint8_t paletteIndex = 0;
  static uint8_t level = 1;

  if (level > 6) {
    level = 1;
  }
  if (paletteIndex > 255) {
    paletteIndex = 0;
  }
  switch (level) {
    case 1: leds[24] = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 2: leds(21, 23) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 3: leds(16, 20) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 4: leds(9, 15) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 5: leds(0, 8) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 6: leds(0, NUM_LEDS - 1) = CRGB::Black;
      break;
    default: leds(0, NUM_LEDS - 1) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
  }

  EVERY_N_MILLISECONDS_I(timingObj, 200) {
    timingObj.setPeriod(animationSpeed);
    level++;
    paletteIndex += 24;
  }
}

void fillUpThenDown() {
  static uint8_t paletteIndex = 0;
  static uint8_t level = 1;

  if (level > 11) {
    level = 1;
  }
  if (paletteIndex > 255) {
    paletteIndex = 0;
  }
  switch (level) {
    case 1: leds(0, 8) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 2: leds(9, 15) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 3: leds(16, 20) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 4: leds(21, 23) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 5: leds[24] = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
    case 6: leds[24].fadeToBlackBy(fadeToBlack);
      break;
    case 7: leds(21, 23).fadeToBlackBy(fadeToBlack);
      break;
    case 8: leds(16, 20).fadeToBlackBy(fadeToBlack);
      break;
    case 9: leds(9, 15).fadeToBlackBy(fadeToBlack);
      break;
    case 10: leds(0, 8).fadeToBlackBy(fadeToBlack);
      break;
    case 11: leds(0, NUM_LEDS - 1) = CRGB::Black;
      break;
    default: leds(0, NUM_LEDS - 1) = ColorFromPalette(gCurrentPalette, paletteIndex, 255);
      break;
  }
  EVERY_N_MILLISECONDS_I(timingObj, 200) {
    timingObj.setPeriod(animationSpeed);
    level++;
    paletteIndex += 24;
  }
}

void christmasTree() {
  static uint8_t i = 0;
  leds[24].fadeToBlackBy(fadeToBlack);
  if (i > NUM_LEDS - 1) {
    i = 0;
  }
  EVERY_N_MILLISECONDS_I(timingObj, 15) {
    timingObj.setPeriod(animationSpeed);
    if (i < 5) {
      leds[i] = CRGB::Green;
    } else if (i < 9) {
      leds[i] = CRGB::Gold;
    } else if (i < 13) {
      leds[i] = CRGB::Green;
    } else if (i < 16) {
      leds[i] = CRGB::Gold;
    } else if (i < 19) {
      leds[i] = CRGB::Green;
    } else if (i < 21) {
      leds[i] = CRGB::Gold;
    } else if (i < 23) {
      leds[i] = CRGB::Green;
    } else if (i < 24) {
      leds[i] = CRGB::Gold;
    } else if (i < 25) {
      if (random8(2) < 1) {
        leds[i] = CRGB::Gold;
      } else {
        leds[i] = CRGB::Green;
      }

    }
    i++;
  }
  //  add_glitter();
}

void fillColumnsFade() {
  static uint8_t i = 0;
  if (i > NUM_LEDS - 1) {
    i = 0;
  }
  EVERY_N_MILLISECONDS_I(timingObj, 15) {

    leds.fadeToBlackBy(fadeToBlack);
    timingObj.setPeriod(animationSpeed);
    leds[columnMap[i]] = CHSV(gHue, 255, 255);
    i++;
    if (i > 5 && i < NUM_LEDS - 1) {
      leds[columnMap[i]] = CHSV(gHue, 255, 255);
      i++;
    }
  }
}

void fillColumns() {
  static uint8_t i = 0;
  if (i > NUM_LEDS - 1) {
    i = 0;
  }
  EVERY_N_MILLISECONDS_I(timingObj, 15) {
    timingObj.setPeriod(animationSpeed);
    leds[columnMap[i]] = CHSV(gHue, 255, 255);
    i++;
    if ((i > 4 && i < NUM_LEDS - 1) || i == NUM_LEDS - 1) {
      leds[columnMap[i]] = CHSV(gHue, 255, 255);
      i++;
    }
  }
}

void diamondFetti () {
  leds.fadeToBlackBy(fadeToBlack);
  uint8_t nums[] = {0,2,4,6,8,10,12,14,16,18,20};
  EVERY_N_MILLISECONDS_I(timingObj, 15) {
    timingObj.setPeriod(animationSpeed);
    uint8_t i = random8(0, 10);
    uint8_t j = nums[i];
    leds[diamondMap[j]] = ColorFromPalette(currentPalette, gHue + (j * 2), 255);
    leds[diamondMap[j + 1]] = leds[diamondMap[j]];
  }


}

