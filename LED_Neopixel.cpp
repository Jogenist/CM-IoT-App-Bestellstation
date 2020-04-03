/*
 * Autor: Sofiane Arouay
 * Date: 12.11.2019
 * Class LED_Neopixel is an interface for the LEDs
 * With this class user can send the defined messages to be displayed
 *  
 */
 
#include"LED_NeoPixel.h"

  // Neo Pixel
#define PixelsCount 24      // Number of LEDs 
#define PIN 15              // Pin connected to the LEDs
#define BRIGHTNESS 50       // Brightness of the LEDs
#define colorSaturation 80 

  byte neopix_gamma[] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
  2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
  5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
  10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
  17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
  25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
  37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
  51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
  69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
  90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

// this array is used to change the brightness of LEDs to make them flash
  byte neopix_brightness[] = {
    2,  4,  7,  9,  13,  17,  25,  35,  50,  75,  95,  105, 120,  135,  155,  165,
    180,  200,  215,  220,  230,  240,  250,  255 };
  
  // constr
  LED::LED():pixels(NULL),altStatus(0xFF)
  {
	  pixels = new Adafruit_NeoPixel(PixelsCount, PIN, NEO_RGBW + NEO_KHZ800);
  }
  
  LED::~LED()
  {
	  delete pixels;
  }
  
  // Setup for the LEDs need to be called in the start
  bool LED::setupLED()
  {
	  pixels->begin();
    pixels->setBrightness(BRIGHTNESS);
    pixels->clear();
    return true;
  }
  
  // this function make the LEDs flash to show either a success or error message ;the variable Success defines the type of the message
  bool LED::Blinken(bool Success)
  {
	  uint32_t color; 
	  if(Success)
	  {
		  for (int j = 0; j < 256; j++) 
		  {		  
              for (uint16_t i = 0; i < pixels->numPixels(); i++) {
              pixels->setPixelColor(i, pixels->Color(128, 0, 0, neopix_gamma[j]));
          }
          delay(3);
          pixels->show();
          }

          for (int j = 255; j >= 0; j--)
		  {			  
               for (uint16_t i = 0; i < pixels->numPixels(); i++) {
               pixels->setPixelColor(i, pixels->Color(128, 0, 0, neopix_gamma[j]));
          }
          delay(3);
          pixels->show();
          } 
	  }
	  else
	  {
		  for (int j = 0; j < 256; j++) 
		  {		  
              for (uint16_t i = 0; i < pixels->numPixels(); i++) {
              pixels->setPixelColor(i, pixels->Color(35, 220, 21, neopix_gamma[j]));
          }
          delay(3);
          pixels->show();
          }

          for (int j = 255; j >= 0; j--)
		  {			  
               for (uint16_t i = 0; i < pixels->numPixels(); i++) {
               pixels->setPixelColor(i, pixels->Color(35, 220, 21, neopix_gamma[j]));
          }
          delay(3);
          pixels->show();
          } 
	  }
	  return true;
  }
  
  // this function is called from the user with new Status to be displayed 
  bool LED::showLED(uint8_t PixelState)
  {
	  if(PixelState==altStatus)
   {
		  return true;
   }
    pixels->clear();
	  altStatus = PixelState;
	  switch (PixelState)
	  {
		  case ANZEIGE_ERFOLG:
      {
		  Blinken(true);
		  break;
      }
		  case ANZEIGE_FEHLER:
      {
		  Blinken(false);
		  break;
      }
		  case ANZEIGE_WELCOME:
     {
		  for (uint16_t i = 0; i < pixels->numPixels(); i++) 
		  {
			  pixels->setPixelColor(i, pixels->Color(15, 10, 5, 120));
		  }
			pixels->show();
		  break;
     }
		  case ANZEIGE_WRITE:
     {
		  for (uint16_t i = 0; i < pixels->numPixels(); i++) 
		  {
			  pixels->setPixelColor(i, pixels->Color(15, 90, 105, 10));
		  }
			pixels->show();
		  break;
     }
		  default:
      {
		  altStatus = ANZEIGE_WELCOME;
		  for (uint16_t i = 0; i < pixels->numPixels(); i++) 
		  {
			  pixels->setPixelColor(i, pixels->Color(15, 10, 5, 120));
		  }
			pixels->show();
		  break;
      }
	  }
	  return true;
  }
   
