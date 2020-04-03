/*
 * Autor: Sofiane Arouay
 * Date: 12.11.2019
 * Class LED_Neopixel is an interface for the LEDs
 * With this class user can send the defined messages to be displayed
 *  
 */
#ifndef _LED_NEOPIXEL_H
#define _LED_NEOPIXEL_H


#include "U8g2lib.h"
#include <cmath>
#include "Adafruit_GFX.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>





#define ANZEIGE_ERFOLG 2
#define ANZEIGE_FEHLER 3
#define ANZEIGE_WRITE  1
#define ANZEIGE_WELCOME 0




class LED
{
public:
	LED();
	~LED();
	
	// this function is called from the user with new Status to be displayed 
	bool showLED(uint8_t PixelState);
	
	// Setup for the LEDs need to be called in the start
    bool setupLED();                   
	
	// this function make the LEDs flash to show either a success or error message ;the variable Success defines the type of the message
	bool Blinken(bool Success);
	
private:

  Adafruit_NeoPixel* pixels;  //LEDs
  
  // old status: make sure that the new message should be changed if it is different from the old one
  uint8_t altStatus;	
	
};




#endif
