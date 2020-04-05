/*
 * Autor: Sofiane Arouay
 * Date: 02.10.2019
 * Class MFRC522_Erweiterung as an extension for MFRC522
 * Class RFID_Card is aimed to read/write Data for Cocktail machine purposes, for example to order a drink or read drinks quantity
 * The MFRC522_I2C library is needed: either it is installed in Arduino IDE or added to the project 
 */
 
#ifndef _RFID_H_
#define _RFID_H_

#include <cstdlib>
#include "Arduino.h"
#include "MFRC522_I2C.h"

/* define DEBUG_RFID to get messages in serial monitor for debug purposes*/

 //#define DEBUG_RFID       // Uncomment for serial messages

/* Blockadresses definiton */
#define BESTELLUNG_STATUS  12        // The order is writing in Blockaddr 12 (0. block from sector 3)
//#define BESTELLUNG_ERFOLG 13   // Ordersuccess is writing in Blockaddr 13 (1. block from sector 3)
#define COCKTAILNAME 9
#define CUSTOMCOCKTAILNAME 8 //jg0402 location 

#define BESTELLT 0xFF
#define BEFUELLT 0x00

enum RFIDerrorcode
{
	RFID_OK,				// Everything ok
	RFID_FCARDSERIAL,		// Failed to read current card serial
//	RFID_FUIDIDENTICAL,		// UID matches last UID -> card read twice
	RFID_FDRINKSTATUS,		// Can't read drink status
	RFID_FWRONGSTATUS,		// Unexpected Status
	RFID_FDATAREAD,			// Failed to read RFID data
	RFID_FMIXERQUEUE,		// Unable to add order to mixer queue
	RFID_FWRITECARD,		// Exception while trying to write the card
	RFID_NOCARD             // no new card available

};


/*
 * this class is an extension for the class MFRC522. With this extension the manipulation of RFID chip 
 * would be easier. 
*/
class MFRC522_Erweiterung : public MFRC522
{
public:

  MFRC522_Erweiterung(const byte &chipAddress = 0x28, const byte &resetPowerDownPin = 5);

  ~MFRC522_Erweiterung();

  // read a block, stdkey is used wenn no key is given
  // Buffersize must be at least 18 byte
  bool readBlock(const uint8_t& blockaddr, byte& Buffer, byte size, MIFARE_Key* pKey = NULL); 

  // Write a block, stdkey is used wenn no key is given
  // buffer must be at 16 byte
  bool writeBlock(const uint8_t& blockaddr, byte* Buffer, const byte& size, MIFARE_Key *pKey = NULL);  

  // Change the secret Key A of a sector
  bool changeSectorSecretKey(const byte& sectoraddr, MIFARE_Key& oldKey, MIFARE_Key& newKey); 

#ifdef DEBUG_RFID
  bool setverborse(const bool& pVerborse);
#endif // DEBUG_RFID


  // Get the last error code (StatusCode defined in MFRC522)
  StatusCode getlasterrorcode()
  {
    return errcode;
  }

  
private:

	StatusCode errcode;

#ifdef DEBUG_RFID

	bool verborse;
#endif // DEBUG_RFID

  MIFARE_Key stdKey; // Factory key: 0xFFFFFFFFFFFF

};



class RFID_Card
{
public:

	RFID_Card(const byte& pchipAddress = 0x28, const byte& presetPowerDownPin = 5);

	~RFID_Card();

	// initialize the MFRC522 sensor
	void init();

	RFIDerrorcode checkIsHITglas();

	RFIDerrorcode writeOrder(const char* Order, int Size);

  //RFIDerrorcode writeCustomOrder(const char* Order, int Size);

	RFIDerrorcode readOrder(char* Order,int size, byte& Status); //


	RFIDerrorcode writeCocktailStatus(byte Status);

	RFIDerrorcode readCocktailStatus(byte& Status);

	MFRC522_Erweiterung Sensor;

private:

	MFRC522::MIFARE_Key HITKey; // Used for sector 3: 0xFAFBFCFDFEFF

	byte chipAddress;
	byte resetPowerDownPin;


#ifdef DEBUG_RFID
	bool verborse;
#endif // DEBUG_RFID

};







#endif
