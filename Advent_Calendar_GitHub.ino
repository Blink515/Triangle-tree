// A good chunk of this code is borrowed from https://github.com/evilgeniuslabs/tree-v2

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#define BLYNK_MAX_SENDBYTES 512 // Default is 128
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "FastLED.h"

// LEDs
#define LED_PIN D6
#define NUM_LEDS 25
#define ZOOMING_BEATS_PER_MINUTE 128

uint8_t gCurrentPaletteNumber = 0;
uint8_t secondsPerPalette = 20;
extern const TProgmemRGBGradientPalettePtr gGradientPalettes[];
CRGBPalette16 currentPalette;
CRGBPalette16 gCurrentPalette( CRGB::Black);
CRGBPalette16 gTargetPalette( gGradientPalettes[0] );

CRGBArray<NUM_LEDS> leds;
int ledMode = 1;
int masterBrightness = 100;
int fadeToBlack = 60;
int animationSpeed = 2;
int paletteNum = 1;
bool randomPaletteRun = 0;
int rainbowDensity = 3;
bool power = 1;
bool isFirstConnect = true;
bool randomPatterns = 0;                  //Whether the LED mode should randomly change
uint8_t secondsToHoldRandomMode = 15;     //Indicates how long to wait before changing LED modes when random mode is active
uint8_t gHue = 0;                         // rotating "base color" used by many of the patterns
uint16_t ledsData[NUM_LEDS][4];           // array to store RGB data and an extra value for Rainbow shifted glitter
uint16_t pick;                            // stores a temporary pixel number for Rainbow shifted glitter animation
bool V2Loaded = false;                    // Determines whether V2 menu widget has been populated
uint8_t glitterChance = 30;               // Determines the percent chance of glitter to add
uint8_t mapNum = 1;                       // Determines which led mapping technique to use.


#include "Map.h"
#include "Animations.h"
#include "Twinkles.h"
#include "TwinkleFOX.h"
#include "Triangles.h"
#include "GradientPalettes.h"

char auth[] = "Auth code from Blynk App";

BLYNK_CONNECTED() {
  if (isFirstConnect) {
    Blynk.syncAll();
  }
}

void setup() {
  //Blynk.begin(auth, "wlanssid", "wlan password", IPAddress(192, 168, 1, 2));  //Use this for a local server replacing the IP address with the server's IP. Use , instead of .
  Blynk.begin(auth, "wlanssid", "wlan password");  //Use this if using Blynk cloud

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // tell FastLED about the LED strip configuration
  //FastLED.addLeds<APA102, 11, 13, RGB, DATA_RATE_MHZ(1)>(leds, NUM_LEDS);
  FastLED.addLeds<WS2811, 13, RGB>(leds, NUM_LEDS).setDither(0);
  // limit my draw to 1.5A at 5v of power draw
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);
  // set master brightness control
  FastLED.setBrightness(masterBrightness);
  Serial.begin(9600);

  
}

void SetupRandomPalette()
{
  currentPalette = CRGBPalette16(
                     CHSV( random8(), 255, 32),
                     CHSV( random8(), 255, 255),
                     CHSV( random8(), 128, 255),
                     CHSV( random8(), 255, 255));
}

void loop() {
  Blynk.run();

  EVERY_N_SECONDS_I(timingObj, 20) {
    timingObj.setPeriod(secondsToHoldRandomMode);
    if (randomPatterns != 0) {
      ledMode = random8(1, 28);
      paletteNum = random8(1, 35);
      Blynk.virtualWrite(V2, ledMode);
      Blynk.virtualWrite(V7, paletteNum);
    }
  }

  EVERY_N_MILLISECONDS( 30 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
  }

  if (paletteNum <= 9) {
    switch (paletteNum) {
      case 1: currentPalette = PartyColors_p;
        randomPaletteRun = 0;
        break;
      case 2: currentPalette = ForestColors_p;
        randomPaletteRun = 0;
        break;
      case 3: currentPalette = LavaColors_p;
        randomPaletteRun = 0;
        break;
      case 4: currentPalette = CloudColors_p;
        randomPaletteRun = 0;
        break;
      case 5: currentPalette = OceanColors_p;
        randomPaletteRun = 0;
        break;
      case 6: currentPalette = RainbowColors_p;
        randomPaletteRun = 0;
        break;
      case 7: currentPalette = RainbowStripeColors_p;
        randomPaletteRun = 0;
        break;
      case 8: currentPalette = HeatColors_p;
        randomPaletteRun = 0;
        break;
      case 9: if (randomPaletteRun == 0) {
          SetupRandomPalette();
          randomPaletteRun = 1;
        } else {
          currentPalette = currentPalette;
        }
        break;
      default: currentPalette = PartyColors_p;
        randomPaletteRun = 0;
        break;
    }
  }

  if (power != 1) {
    leds(0, NUM_LEDS - 1) = CRGB::Black;
    FastLED.show();
  } else {
    switch (ledMode) {
      case 1:
        fill_rainbow( leds, NUM_LEDS, gHue, rainbowDensity);
        break;
      case 2:
        rainbowRandomGlitter();
        break;
      case 3:
        rainbowShiftedGlitter();
        break;
      case 4:
        snowTwinkles();
        break;
      case 5:
        iceTwinkles();
        break;
      case 6:
        snow2Twinkles();
        break;
      case 7:
        fairyLightTwinkles();
        break;
      case 8:
        blueWhiteTwinkles();
        break;
      case 9:
        redWhiteTwinkles();
        break;
      case 10:
        hollyTwinkles();
        break;
      case 11:
        redGreenWhiteTwinkles();
        break;
      case 12:
        retroC9Twinkles();
        break;
      case 13:
        triangle();
        break;
      case 14:
        triangles();
        break;
      case 15:
        spiral();
        break;
      case 16:
        spiralPalette();
        break;
      case 17:
        juggle();
        break;
      case 18:
        bpm();
        break;
      case 19:
        sinelon();
        break;
      case 20:
        confetti();
        break;
      case 21:
        christmasTree();
        break;
      case 22:
        fillUpThenDown();
        break;
      case 23:
        fillUp();
        break;
      case 24:
        fillDown();
        break;
      case 25:
        fillColumns();
        break;
      case 26:
        fillColumnsFade();
        break;
      case 27:
        colorwaves( leds, NUM_LEDS, gCurrentPalette);
        break;
      case 28:
        diamondFetti();
        break;
      default:
        fill_solid(leds, NUM_LEDS - 1, CRGB::Blue);
        break;
    }
  }
  FastLED.setBrightness(masterBrightness);
  FastLED.show();

  // change to a new cpt-city gradient palette
  EVERY_N_SECONDS( secondsPerPalette ) {
    gCurrentPaletteNumber = addmod8( gCurrentPaletteNumber, 1, gGradientPaletteCount);
    gTargetPalette = gGradientPalettes[ gCurrentPaletteNumber ];
    if(ledMode == 27) {
      Blynk.virtualWrite(V7, gCurrentPaletteNumber + 10);
    }
  }

  EVERY_N_MILLISECONDS(40) {
    // slowly blend the current palette to the next
    nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 8);
    //    nblendPaletteTowardPalette(currentPalette, targetPalette, 16);
    gHue++;  // slowly cycle the "base color" through the rainbow
  }
}

BLYNK_WRITE(V0)
{
  //BLYNK_LOG("Got a value: %i", param.asInt());
  ledMode = param.asInt();
}
BLYNK_WRITE(V1)
{
  //BLYNK_LOG("Got a value: %i", param.asInt());
  power = param.asInt();
}
BLYNK_WRITE(V2)
{
  //BLYNK_LOG("Got a value: %i", param.asInt());
  ledMode = param.asInt();
}
BLYNK_WRITE(V3)
{
  //BLYNK_LOG("Got a value: %i", param.asInt());
  masterBrightness = param.asInt();
}
BLYNK_WRITE(V4)
{
  //BLYNK_LOG("Got a value: %i", param.asInt());
  fadeToBlack = param.asInt();
}
BLYNK_WRITE(V5)
{
  //BLYNK_LOG("Got a value: %i", param.asInt());
  rainbowDensity = param.asInt();
}
BLYNK_WRITE(V6)
{
  BLYNK_LOG("Got a value: %i", param.asInt());
  randomPatterns = param.asInt();
}
BLYNK_WRITE(V7)
{
  //BLYNK_LOG("Got a value: %i", param.asInt());
  paletteNum = param.asInt();

  if (paletteNum > 9) {
    gCurrentPalette = gGradientPalettes[param.asInt() - 10];
    currentPalette = gCurrentPalette;
  }
}
BLYNK_WRITE(V8)
{
  //BLYNK_LOG("Got a value: %i", param.asInt());
  animationSpeed = param.asInt();
}
BLYNK_WRITE(V9)
{
  if(param.asInt() == 1 && V2Loaded != true) {
    //Fill the menu widget with animation names
    Blynk.setProperty(V2, "labels", "Rainbow", "Rainbow Random Glitter", "Rainbow Shifted Glitter", 
                                    "Snow Twinkles","Ice Twinkles", "Snow Twinkles 2", "Fairy Light Twinkles", 
                                    "Blue White Twinkles","Red White Twinkles", "Holly Twinkles", "Christmas Twinkles", 
                                    "Retro C9 Twinkles","Triangle", "Triangles", "Spiral", "Spiral Palette","Juggle", 
                                    "BPM", "Sinelon", "Confetti", "Christmas Tree", "Fill Up/Down", "Fill Up","Fill Down", 
                                    "Fill Columns", "Fill Columns Fade", "Color Waves", "Diamonds");
  //V2Loaded = true;
  }
}
BLYNK_WRITE(V10)
{
  //BLYNK_LOG("Got a value: %i", param.asInt());
  glitterChance = param.asInt();
}
BLYNK_WRITE(V11)
{
  //BLYNK_LOG("Got a value: %i", param.asInt());
  mapNum = param.asInt();
}

