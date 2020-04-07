/*
 * Autor: Sofiane Arouay
 * Date: 02.10.2019
 * Class RFID
 */


#include "RFID.h"
#include "MFRC522_I2C.h"


const char Success[] = " ORDER  OKAY! ";
// Cocktails definition

const char* Cocktails[] = { "Wodka-Maracuja","Malibu-Maracuja","Malibu-Orange","Malibu-Sunrise","Screwdriver", // Alc cocktails
"Tropic-Thunder","Mix-Mimi","Pink-Pussycat","Mix-Safari","San-Francisco","The-Waikiki","Mix-Brassmonkey",  // Alc cocktails
"Maracuja","Orange","Taifruitpunch","Tropic-Sunrise","Lemon-Cocktail","Mix-Sixteen",   // non alc cocktails
"Mix-Redone","Mix-Planterswonder","Mix-Targa","Bananajack","Bora-Bora","Drachenblut","Mix-Kiba","Luckydriver","Ananas-Orange", // non alc cocktails
"Babouin","Ballerina","Cinderella","Mix-Sweetvictory","Mix-Sweety","Tropic-Star","Tropical-Orange" }; // non alc cocktails


const char* Zutaten_alk_statisch[]={"Wodka, Maracuja","Malibu, Maracuja","Malibu, Orange","Malibu, Grenadine, Orange","Wodka, Orange",
                                    "Wodka, Malibu, Maracuja","Wodka, Malibu, Ananas","Wodka, Grenadine, Ananas","Wodka, Zitrone",
                                    "Wodka, Maracuja, Ananas, Zitrone, Grenadine, Orange, Banane","Wodka, Ananas","Wodka, Orange(anderes Verhältnis)"};

const char*Zutaten_antialk_statisch[]={"Maracuja","Orange","Maracuja, Orange, Ananas, Zitrone, Grenadine","Banane, Ananas, Maracuja, Grenadine",
                                      "Zitrone, Orange", "Grenadine, Zitrone, Orangen, Maracuja, Ananas","Zitrone, Grenadine, Orangensaft, Ananas","Zitrone, Grenadine, Orange, Maracuja, Ananas",
                                      "Zitrone, Grenadine, Maracuja, Orange, Ananas(anderes Verhältnis)","Grenadine, Zitrone, Orange, Banane"," Zitrone, Grenadine, Maracuja, Ananas",
                                      "Zitrone, Grenadine, Orange, Maracuja", "Ananas, Orange", "Zitrone, Orange, Ananas", "Zitrone, Orange, Ananas(anderes Verhältnis)","Grenadine, Orange, Ananas",
                                      "Orange, Maracuja, Ananas", "Grenadine, Orange, Ananas"}; 


/*
*  class RFID_Card
*
*/

RFID_Card::RFID_Card(const byte& pchipAddress, const byte& presetPowerDownPin):Sensor(pchipAddress, presetPowerDownPin), 
chipAddress(pchipAddress), resetPowerDownPin(presetPowerDownPin)
{
	
}


RFID_Card::~RFID_Card()
{

}


void RFID_Card::init()
{
	Sensor.PCD_Init();
	for (int i = 0; i < 6; i++)
	{
		HITKey.keyByte[i] = 0xFF - i;
	}
}


RFIDerrorcode RFID_Card::checkIsHITglas()
{
	if (Sensor.PICC_IsNewCardPresent())
	{ 
		//check if any cards are present. Must be in the standby mode (not halt mode)
#ifdef DEBUG_RFID
		Serial.println("RFID: new card detected");
#endif  // DEBUG_RFID
    delay(500);
		if (!Sensor.PICC_ReadCardSerial())
		{		//read card serial
			delay(500);
			/*Second trial*/
			if (!Sensor.PICC_ReadCardSerial())
			{
#ifdef DEBUG_RFID
				Serial.println("Failed to read card serial");
#endif  // DEBUG_RFID
      Sensor.PICC_HaltA();
	  delay(100);
	 return RFID_FCARDSERIAL;
			}
		}
#ifdef DEBUG_RFID
		Serial.println("new card serial read");
#endif  // DEBUG_RFID

		return RFID_OK;
	}
	return RFID_NOCARD;
}


RFIDerrorcode RFID_Card::writeOrder(const char* Order, int Size)
{
#ifdef DEBUG_RFID
	Serial.println("Writing order...");
#endif  // DEBUG_RFID
	byte Buffer[32];
	memset(Buffer, 0, 32);
	memcpy(Buffer,Order,Size);
	if (!Sensor.writeBlock(COCKTAILNAME, Buffer, 16))
	{
#ifdef DEBUG_RFID
		Serial.println("Failed to write order");
#endif  // DEBUG_RFID
		return RFID_FWRITECARD;
    }
	if (!Sensor.writeBlock(COCKTAILNAME+1, &Buffer[16], 16))
	{
#ifdef DEBUG_RFID
		Serial.println("Failed to write order");
#endif  // DEBUG_RFID
		return RFID_FWRITECARD;
	}
	byte CheckBuffer[32];
	memset(CheckBuffer, 0, 16);
	if (writeCocktailStatus(BESTELLT)!=RFID_OK)  // write an other block for order success writing
	{
#ifdef DEBUG_RFID
		Serial.println("Failed to write order success");
#endif  // DEBUG_RFID
		return RFID_FWRITECARD;
	}
#ifdef DEBUG_RFID
	Serial.println("write order okay");
#endif  // DEBUG_RFID
	return RFID_OK;
}

RFIDerrorcode RFID_Card::readOrder(char* Cocktail, int size, byte& Status)
{
#ifdef DEBUG_RFID
	Serial.println("Reading order...");
#endif  // DEBUG_RFID
	byte Buffer[32];
	if (!Sensor.readBlock(COCKTAILNAME, Buffer[0], 16))
	{
#ifdef DEBUG_RFID
		Serial.println("Failed to read order");
#endif  // DEBUG_RFID
		return RFID_FDATAREAD;
	}
	if (!Sensor.readBlock(COCKTAILNAME+1, Buffer[16], 16))
	{
#ifdef DEBUG_RFID
		Serial.println("Failed to read order");
#endif  // DEBUG_RFID
		return RFID_FDATAREAD;
	}
	for (int i=0; i < size; i++)
	{
		if (Buffer[i] == 0)
			break;
		Cocktail[i] = Buffer[i];
	}
	if (readCocktailStatus(Status) != RFID_OK)
	{
#ifdef DEBUG_RFID
		Serial.println("Failed to read order status");
#endif  // DEBUG_RFID
		return RFID_FDATAREAD;
	}
	return RFID_OK;
}



RFIDerrorcode RFID_Card::writeCocktailStatus(byte Status)
{
	byte Buffer[16];
	memset(Buffer, Status, 16);
	Buffer[1] = Status;
	if (!Sensor.writeBlock(BESTELLUNG_STATUS, Buffer, 16, &HITKey))
	{
#ifdef DEBUG_RFID
		Serial.println("Failed to write order status");
#endif  // DEBUG_RFID
		return RFID_FDATAREAD;
	}
	return RFID_OK;
}

RFIDerrorcode RFID_Card::readCocktailStatus(byte& Status)
{
	byte Buffer[16];
	if (!Sensor.readBlock(BESTELLUNG_STATUS, Buffer[0], 16, &HITKey))
	{
#ifdef DEBUG_RFID
		Serial.println("Failed to read order status");
#endif  // DEBUG_RFID
		return RFID_FDATAREAD;
	}
	Status = Buffer[1];
	return RFID_OK;
}


/*
* class MFRC522_Erweiterung
* 
*/





MFRC522_Erweiterung::MFRC522_Erweiterung(const byte& chipAddress, const byte& resetPowerDownPin) : MFRC522(chipAddress, resetPowerDownPin), errcode(STATUS_OK)
{
#ifdef DEBUG_RFID
	verborse = true;
#endif	// DEBUG_RFID
	for (int i = 0; i < 6; i++)
		stdKey.keyByte[i] = 0xFF;
}


MFRC522_Erweiterung::~MFRC522_Erweiterung()
{

}


bool MFRC522_Erweiterung::readBlock(const uint8_t& blockaddr, byte& Buffer, byte size, MIFARE_Key* pKey)
{
	
#ifdef DEBUG_RFID
	if (verborse)	
		Serial.printf("Reading block %d ... \n", blockaddr);
#endif  // DEBUG_RFID
	byte Buff[18];
	StatusCode status;
	if (pKey == NULL)
		pKey = &stdKey;
	status = (StatusCode) PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, ((blockaddr / 4) * 4 +3), pKey, &(uid));
	if (status != STATUS_OK)
	{
#ifdef DEBUG_RFID
		if (verborse)
		{
			Serial.println("Authentication failed for readBlock()");
			Serial.println(GetStatusCodeName(status));
		}
#endif  // DEBUG_RFID
		errcode = status;
		return false;
	}
	byte pSize=18;
	status = (StatusCode) MIFARE_Read(blockaddr, &Buff[0], &pSize);
	if (status != STATUS_OK)
	{
#ifdef DEBUG_RFID
		if (verborse)
		{
			Serial.println("Reading failed for readBlock()");
			Serial.println(GetStatusCodeName(status));
		}
#endif  // DEBUG_RFID
		errcode = status;
		return false;
	}
	memcpy(&Buffer, Buff, size);
#ifdef DEBUG_RFID
	if (verborse)	
		Serial.printf("%d. Block successfully read \n", blockaddr);
#endif  // DEBUG_RFID
	return true;
}


bool MFRC522_Erweiterung::writeBlock(const uint8_t& blockaddr, byte* Buffer, const byte& size, MIFARE_Key* pKey)
{
#ifdef DEBUG_RFID
	if (verborse)	
		Serial.printf("Writing block %d ... \n", blockaddr);
#endif  // DEBUG_RFID
	if (pKey == NULL)
		pKey = &stdKey;
	if (Buffer == NULL || size < 16)
	{
#ifdef DEBUG_RFID
		if (verborse)
			Serial.println("Buffersize must be 16 bytes");
#endif  // DEBUG_RFID
		errcode = STATUS_NO_ROOM;
		return false;
	}
	StatusCode status = (StatusCode)PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, ((blockaddr / 4)*4 + 3), pKey, &(uid));
	if (status != STATUS_OK)
	{
#ifdef DEBUG_RFID
		if (verborse)
		{
			Serial.printf("Authentication failed for writeBlock().. Errcode: %d \n",status);
			Serial.println(GetStatusCodeName(status));
		}
#endif  // DEBUG_RFID
		errcode = status;
		return false;
	}
	status = (StatusCode) MIFARE_Write(blockaddr, Buffer, size);
	if (status != STATUS_OK)
	{
#ifdef DEBUG_RFID
		if (verborse)
		{
			Serial.println("Writing failed for writeBlock()");
			Serial.println(GetStatusCodeName(status));
		}
#endif  // DEBUG_RFID
		errcode = status;
		return false;
	}
#ifdef DEBUG_RFID
	if (verborse)	
		Serial.printf("%d. Block is written with success \n", blockaddr);
#endif  // DEBUG_RFID
	return true;
}


bool MFRC522_Erweiterung::changeSectorSecretKey(const byte& sectoraddr, MIFARE_Key& oldKey, MIFARE_Key& newKey)
{
#ifdef DEBUG_RFID
	if (verborse)	
		Serial.println("Changing secret key ...");
#endif  // DEBUG_RFID
	if (sectoraddr > 15)
	{
#ifdef DEBUG_RFID
		if (verborse)
			Serial.println("Sectoraddr is false");
#endif  // DEBUG_RFID
		return false;
	}
	byte Sectortraileraddr = sectoraddr * 4 + 3;
	StatusCode status = (StatusCode) PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, Sectortraileraddr, &oldKey, &(uid));
	if (status != STATUS_OK)
	{
#ifdef DEBUG_RFID
		if (verborse)
		{
			Serial.println("Oldkey is false. Could not authenticate!");
			Serial.println(GetStatusCodeName(status));
		}
#endif  // DEBUG_RFID
		errcode = status;
		return false;
	}
	byte Buffer[18];
	memcpy(Buffer, newKey.keyByte,6);
	Buffer[6] = 0xFF; // Access bits setup (need keyA for all functions (read/write)
	Buffer[7] = 0x07;
	Buffer[8] = 0x80;
	Buffer[9] = 0x69;
	for (int i = 10; i < 16; i++)
	{
		Buffer[i] = 0xFF;
	}
	status = (StatusCode) MIFARE_Write(Sectortraileraddr, Buffer, 16);
	if (status != STATUS_OK)
	{
#ifdef DEBUG_RFID
		if (verborse)
		{
			Serial.println("Could not write new key");
			Serial.println(GetStatusCodeName(status));
		}
#endif  // DEBUG_RFID
		errcode = status;
		return false;
	}
	status = (StatusCode) PCD_Authenticate(PICC_CMD_MF_AUTH_KEY_A, Sectortraileraddr, &newKey, &(uid));
	if (status != STATUS_OK)
	{
#ifdef DEBUG_RFID
		if (verborse)
		{
			Serial.println("Could not authenticate new key.");
			Serial.println(GetStatusCodeName(status));
		}
#endif  // DEBUG_RFID
		errcode = status;
		return false;
	}

#ifdef DEBUG_RFID
	if (verborse)	
		Serial.println("Auth new key okay.");
#endif  // DEBUG_RFID
	byte size = 18;
	status = (StatusCode) MIFARE_Read(Sectortraileraddr, Buffer, &size);
	if (status != STATUS_OK)
	{
#ifdef DEBUG_RFID
		if (verborse)
		{
			Serial.println("Could not read new key.");
			Serial.println(GetStatusCodeName(status));
		}
#endif  // DEBUG_RFID
		errcode = status;
		return false;
	}

#ifdef DEBUG_RFID
	if (verborse)	
		Serial.println("Read new key okay.");
#endif  // DEBUG_RFID

#ifdef DEBUG_RFID
	if (verborse)
		Serial.println("Secret Key successfully changed");
#endif  // DEBUG_RFID
	return true;
}



#ifdef DEBUG_RFID
bool MFRC522_Erweiterung::setverborse(const bool& pVerborse)
{
	verborse = pVerborse;
	Serial.println(verborse ? "Verborse mode enabled" : "Verborse mode disabled");
	return true;
}
#endif // DEBUG_RFID
