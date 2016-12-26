void triangle() {
  leds.fadeToBlackBy(fadeToBlack);

  static uint8_t triNum = 1;
   EVERY_N_MILLISECONDS_I(timingObj, 1) {
    timingObj.setPeriod(animationSpeed);
    triNum++;
  }
  if(triNum >7) {
    triNum = 1;
  }
  switch(triNum) {
    case 1: leds[14] = CRGB::Red;
      break;
    case 2: leds[14] = leds[11] = leds[10] = leds[17] = CRGB::Red;
      break;
    case 3: fill_solid(leds, NUM_LEDS,CRGB::Red);
      break;
    case 4: fill_solid(leds, NUM_LEDS,CRGB::Green);
      break;
    case 5: fill_solid(leds, NUM_LEDS,CRGB::Green);
            leds[14] = CRGB::Black;
      break;
    case 6: fill_solid(leds, NUM_LEDS,CRGB::Green);
            leds[14] = leds[11] = leds[10] = leds[17] = CRGB::Black;
      break;
    case 7: fill_solid(leds, NUM_LEDS, CRGB::Black);
      break;
    default:leds[14] = CRGB::Red;
      break;
  }
  add_glitter();
}

void triangles() {
  leds.fadeToBlackBy(fadeToBlack);

  static uint8_t triNum = 1;
  EVERY_N_MILLISECONDS_I(timingObj, 1) {
    timingObj.setPeriod(animationSpeed);
    triNum++;
  }
  if(triNum >4) {
    triNum = 1;
  }
  switch(triNum) {
    case 1: leds[0] = leds[1] = leds[8] = leds[9] = CRGB::Red;
      break;
    case 2: leds(3,5) = leds[12] = CRGB::Green;
      break;
    case 3: leds[10] = leds[11] = leds[14] = leds[17] = CRGB::Red;
      break;
    case 4: leds(21,24) = CRGB::Green;
      break;
    default:leds[14] = CRGB::Red;
      break;
  }
}

