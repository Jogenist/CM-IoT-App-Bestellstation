/*
 * Autor: Sofiane Arouay
 * Date: 10.11.2019
 * Class DISPLAY_SSH1106 is an interface for the Display SSH1106
 * With this class user can send the defined messages to be displayed 
 *  
 */


#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "Adafruit_GFX.h"
#include <SPI.h>
#include <Wire.h>
#include "U8g2lib.h"
#include <WiFi.h>

#define hska_logo_width 57
#define hska_logo_height 64
#define Arrow_width 40
#define Arrow_height 40
#define Wrong_width 50
#define Wrong_height 48
#define Cocktail_width 40
#define Cocktail_height 50

#define ROUTERINFO 0
#define WELCOME    1
#define MSUCCESS   2
#define MFEHLER    3
#define ORDERINFO  4 

class DISPLAY_SSH1106
{
public:
	DISPLAY_SSH1106();
	~DISPLAY_SSH1106();
	bool displaybegin();                     // Setup for the display need to be called in the start
	bool Message_fehler();                   // display error message 
	bool Message_success();                  // display success message
	bool OrderInfo();                        // display this message when an order has been made in the website 
	bool Message_welcome();                  // welcome message displayed when the Bestellstation is at rest
	bool RouterInfo();                       // display that the Bestellstation is still trying to connect to the router
	bool Message_IPAdress(IPAddress IP);
	bool displaycurrentStat(uint8_t Status); // display the right message given the status. With this function no need to try and 
    
private:
	U8G2_SH1106_128X64_NONAME_F_HW_I2C* Display_SSH1106; // SSH1106 Display
	// old status: make sure that the new message should be changed if it is different from the old one
	uint8_t altStatus;                                   
};






#endif
