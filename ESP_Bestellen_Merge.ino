/*
Type:		Program
Date:		14.08.2019
Author:		Tim Schanz
Description:	The main program setup and loop. configureing and starting the async webserver. The files and contents are send to the client depending on the request. Configuration information are stored in a json file on SPIFFS. Data is transfered between configuration page and main page as a html post.
*/


#include <SPIFFS.h>
#include <WiFi.h>
#include <FS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <string.h>
#include <ArduinoJson.h>
#include "Display_SSH1106.h"
#include "LED_Neopixel.h"
#include "RFID.h"
#include "ESPnow.h"
using namespace std;


#include "index.h"
#include "settings.h"
#include "CustomCocktails.h"    //scch
#include "leertrinkbetrieb.h"
#include "bootstrap.min.css.h"
#include "design.css.h"
#include "JS.h"
/* rofa */
#include "functions.h"

const char* assid = "Xperia";
const char* apassword = "133713371337";

const char* cssid = "";
const char* cpassword = "";
//string html_head;
string index_html;
string settings_html;
string empty_drink_mode_html;
string custom_html;             //scch
AsyncWebServer server(80);

RFID_Card myRFID;
DISPLAY_SSH1106 myDisplay;
LED myLED;
bool isAlc=false;
char myCocktail[32];
bool oderReady = false;
uint8_t myStatus = 0;
SemaphoreHandle_t xAnzeigeSemaphore = NULL;
SemaphoreHandle_t xRFIDSemaphore = NULL;
RFIDerrorcode Status;



/* rofa */
cWifiESPNow ESPnow_object;
bool incomingByte[8]={false};
bool receive_data=false;
int counter= 0;
void permissionstart1();
void permissionstart2(char param);
bool getstarted= false;
char counter2=0;


/* All Ingredients */
bool grenadine = false;
bool zitrone = false;
bool wodka = false;
bool orange = false;
bool maracuja = false;
bool malibu = false;
bool ananas = false;
bool banane = false;

bool auswertungs_array[8]={true, true, true, true, true, true, true, true};


bool *pointer_to_auswertungs_array;

void justtrying();

extern bool alcoholic_cocktails[];
extern bool non_alcoholic_cocktails[];

/* rofa */

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
// this Task deals with RFID	
void RFID(void *)
{
  //Serial.print("RFID:\t");
  //Serial.println(xPortGetCoreID());
  while(true)
  {
	  if(xSemaphoreTake(xRFIDSemaphore, (TickType_t)10) == pdTRUE)
	  {
      Serial.println("Order ready");
      myDisplay.displaycurrentStat(ORDERINFO);
      myLED.showLED(ANZEIGE_WRITE);
		  while((Status = myRFID.checkIsHITglas()) == RFID_NOCARD)
		  {
			  vTaskDelay(10);
		  }
     
		  if(Status == RFID_OK)
		  {
			  if (myRFID.writeOrder(myCocktail, 32) == RFID_OK)
			  {
				  if(myRFID.writeCocktailStatus(BESTELLT) == RFID_OK)
				  {
					  myStatus = ANZEIGE_ERFOLG;
            myDisplay.displaycurrentStat(MSUCCESS);
            myLED.showLED(ANZEIGE_ERFOLG);
					  xSemaphoreGive(xAnzeigeSemaphore);
					  vTaskDelay(300);
				  }
         
				  else
		          {
			          myStatus = ANZEIGE_FEHLER;
			          xSemaphoreGive(xAnzeigeSemaphore);
                myDisplay.displaycurrentStat(MFEHLER);
                myLED.showLED(ANZEIGE_FEHLER);
			          vTaskDelay(300);
		          }
			  }
			  else
		      {
			      myStatus = ANZEIGE_FEHLER;
			      xSemaphoreGive(xAnzeigeSemaphore);
            myDisplay.displaycurrentStat(MFEHLER);
            myLED.showLED(ANZEIGE_FEHLER);
			      vTaskDelay(300);
		      }
		  }
     
		  else
		  {
			  myStatus = ANZEIGE_FEHLER;
			  xSemaphoreGive(xAnzeigeSemaphore);
        myDisplay.displaycurrentStat(MFEHLER);
        myLED.showLED(ANZEIGE_FEHLER);
			  vTaskDelay(300);
		  }
     
		 myRFID.Sensor.PICC_HaltA();
     myRFID.Sensor.PCD_StopCrypto1(); 
		 vTaskDelay(500);
		 myStatus = ANZEIGE_WELCOME;
     myDisplay.displaycurrentStat(WELCOME);
     myLED.showLED(ANZEIGE_WELCOME);
		 xSemaphoreGive(xAnzeigeSemaphore);	 
	  }
		  
    vTaskDelay(100);
  } 
}

// this Task deals with displaying messages both on SSH1106 display and LEDs
void Anzeige(void *)
{
  while(true)
  {
    if(xSemaphoreTake(xAnzeigeSemaphore, (TickType_t)10) == pdTRUE)
    {
      oderReady=false;
      for(int i=0;i<32;i++)
      {
        Serial.print(myCocktail[i]);
      }
      
      myDisplay.displaycurrentStat(myStatus);
      myLED.showLED(myStatus);
	    xSemaphoreGive(xRFIDSemaphore);
      Serial.println();
    }
    vTaskDelay(50);
  }
}

String processor(const String& var)
{
  //Serial.print("WEBSERVER:\t");
	//Serial.println(xPortGetCoreID());
	String price_alc;
	String price_nonalc;
	File filec = SPIFFS.open("/config.json", FILE_READ);
	if (!filec) {
		Serial.println("There was an error opening the file /config.json for reading");
		return "JAVASCRIPT VARIABLE ERROR IN CONFIG FILE READ!\n";
	}

	StaticJsonDocument<512> doc;
	// Deserialize the JSON document
	DeserializationError error = deserializeJson(doc, filec);
	if (error)
	{
		Serial.println(var);

		if (var == "PLACEHOLDER_DEPOSIT") {
			return String("true");
		}

		else if (var == "PLACEHOLDER_PRICE_ALC") {
			return String(5);
		}
		else if (var == "PLACEHOLDER_PRICE_NONALC")
		{
			return String(4);
		}
	}
	else
	{
		Serial.println(var);
		String deposit = doc["deposit_radios"];
		bool with_deposit = false;
		if (deposit.equals("deposit"))
		{
			with_deposit = true;
		}
		else
		{
			with_deposit = false;
		}


		if (var == "PLACEHOLDER_DEPOSIT") {
			if (with_deposit == true)
			{
				return String("true");
			}
			else
			{
				return String("false");
			}
			
		}
		else if (var == "PLACEHOLDER_PRICE_ALC") {
			price_alc = doc["price_alc"].as<const char*>();
			return String(price_alc);
		}
		else if (var == "PLACEHOLDER_PRICE_NONALC")
		{
			price_nonalc = doc["price_nonalc"].as<const char*>();
			return String(price_nonalc);
		}
	}
	return String();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  //setCpuFrequencyMhz(80);
	Serial.begin(115200);
   Wire.begin();
  myRFID.init();
  myDisplay.displaybegin();
  myLED.setupLED();
  vSemaphoreCreateBinary(xAnzeigeSemaphore);
  vSemaphoreCreateBinary(xRFIDSemaphore);
	// Initialize SPIFFS
	if (!SPIFFS.begin(true)) {
		Serial.println("An Error has occurred while mounting SPIFFS");
		return;
	}



Serial.println(WiFi.macAddress()); 
 

	SPIFFS.remove("/design.css");
	SPIFFS.remove("/bootstrap.min.css");
	//SPIFFS.remove("/Default_Config.txt");
	//SPIFFS.remove("/Default_Config.wtxt");
	//SPIFFS.remove("/Werkseinstellungen.xtxt");
	//SPIFFS.remove("/Config_Select.wtxt");
	//SPIFFS.remove("/Config_Select.txt");
	
	//Write the custom css from "design.css.h" with variable Design to FS
	if (!SPIFFS.exists("/design.css"))
	{	
		Serial.println("design.css does not exist. Creating...");
		File filed = SPIFFS.open("/design.css", FILE_WRITE);
		if (!filed) {
			Serial.println("There was an error opening the file /design.css for writing");
			return;
		}
		if (filed.print(Design)) {
			Serial.println("File /design.css was written");
		}
		else {
			Serial.println("File /design.css write failed");
		}

		filed.close();
	}
	//Write the bootstrap css from "bootstrap.min.css.h" with variable Bootstrap to FS
	if (!SPIFFS.exists("/bootstrap.min.css"))
	{
		Serial.println("bootstrap.min.css does not exist. Creating...");
		File fileb = SPIFFS.open("/bootstrap.min.css", FILE_WRITE);
		if (!fileb) {
			Serial.println("There was an error opening the file /bootstrap.min.css for writing");
			return;
		}
		if (fileb.print(Bootstrap)) {
			Serial.println("File /bootstrap.min.css was written");
		}
		else {
			Serial.println("File /bootstrap.min.css write failed");
		}

		fileb.close();
	}
	//Show files in FS
	File root = SPIFFS.open("/");
	File filer = root.openNextFile();
	 
	while (filer) {
		Serial.print("FILE: ");
		Serial.println(filer.name());
		filer = root.openNextFile();
	}

	myDisplay.displaycurrentStat(ROUTERINFO);
	//Start WiFi
	int connection_retry = 0;
 WiFi.mode(WIFI_AP);
	WiFi.begin(assid, apassword);

	while (WiFi.status() != WL_CONNECTED  && connection_retry<=10) {
		delay(2000);
		Serial.print("Connecting to WiFi...  Retry: ");
		Serial.print(connection_retry);
		Serial.print("\n");
		connection_retry++;
	}

	if(WiFi.status() != WL_CONNECTED)
	{ 
		WiFi.mode(WIFI_AP); //Access Point mode
    //WiFi.softAP("TEST", NULL,0);
		WiFi.softAP(assid, apassword);
		Serial.print("SSID: ");
		Serial.print(assid);
		Serial.print("\n");
		Serial.print("PW: ");
		Serial.print(apassword);
		Serial.print("\n");
		IPAddress IP = WiFi.softAPIP();
		Serial.print("AP IP address: ");
		Serial.println(IP);
	}
	else
	{
		Serial.print("SSID: ");
		Serial.print(cssid);
		Serial.print("\n");
		Serial.print("PW: ");
		Serial.print(cpassword);
		Serial.print("\n");
		IPAddress IP = WiFi.localIP();
		Serial.print("IP address: ");
		Serial.println(IP);
	}
	
	
	//htm_head.append(HTML_Head);
	//Answer request for index page
	index_html.append(MAIN_page_Begin);
	index_html.append(dynamic_content_alc());
	index_html.append(MAIN_page_Between);
	index_html.append(dynamic_content_nonalc());
	index_html.append(MAIN_page_AfterFooter_BeforeScript);
	//index_html.append(dynamic_content_javascript());
	index_html.append(JAVASCRIPT_static);
	index_html.append(MAIN_page_AfterFooter_AfterScript);
	server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) { 
  AsyncWebServerResponse *response = request->beginResponse(200);
		request->send_P(200, "text/html", index_html.c_str(), processor);
		});



  server.on("/Bestellung", HTTP_POST,
    [](AsyncWebServerRequest* request) {},
    NULL,
    [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total)
  {

      int ii;
      for (size_t i = 0; i < len; i++) 
      {
        myCocktail[i] = data[i];
        Serial.print(myCocktail[i]);
      }
     for(size_t i =len; i<32; i++)
     {
        myCocktail[i] = 0;
     }
   Serial.println();
   xSemaphoreGive(xAnzeigeSemaphore);
   oderReady = true;
   Serial.println("Bestellung Display");
   Serial.println("Bestellung fertig");
   xSemaphoreGive(xRFIDSemaphore);
   request->send(200);
    });
   

  /* Image, Design */
	//Favicon
	server.on("/image/favico.ico", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, "/favico.ico", "image/x-icon");
		});

	//Logo
	server.on("/image/hska_logo.png", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, "/hska_logo.png", "image/png");
	});


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Answer request for Settings page
	settings_html.append(SETTINGS_page_Begin);
	settings_html.append(SETTINGS_page_After);
	server.on("/settings", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(200, "text/html", settings_html.c_str());
		});

   //Answer request for custom page //scch
  custom_html.append(CUSTOM_page_Begin);
  custom_html.append(CUSTOM_page_AfterFooter_BeforeScript);
  custom_html.append(JAVASCRIPT_static);
  custom_html.append(CUSTOM_page_AfterFooter_AfterScript);
  server.on("/custom", HTTP_GET, [](AsyncWebServerRequest* request) { 
  AsyncWebServerResponse *response = request->beginResponse(200);
    request->send_P(200, "text/html", custom_html.c_str(), processor);
    });

    //Answer request for empty drink mode page//////////////////////////////////////////////////////////////////////////////////////////////
   empty_drink_mode_html.append(LEERTRINKBETRIEB_page_Begin);
   empty_drink_mode_html.append(dynamic_content_leertrinkbetrieb_alc());
   empty_drink_mode_html.append(LEERTRINKBETRIEB_page_middle);
   empty_drink_mode_html.append(dynamic_content_leertrinkbetrieb_nonalc());
   empty_drink_mode_html.append(LEERTRINKBETRIEB_page_After);
   empty_drink_mode_html.append(JAVASCRIPT_static);
   empty_drink_mode_html.append(LEERTRINKBETRIEB_page_AfterScript);
 // server.on("/empty_drink_mode", HTTP_GET, [](AsyncWebServerRequest* request) {
 //   request->send(200, "text/html", empty_drink_mode_html.c_str());
  server.on("/empty_drink_mode", HTTP_GET, [](AsyncWebServerRequest* request){
    AsyncWebServerResponse * response= request->beginResponse(200);
    request-> send_P(200,"text/html",empty_drink_mode_html.c_str(), processor);
    });

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////vmtl. muss hier etwas eingebunden werden, um Bestellungen in der empty_drink_mode aufzugeben!

/*
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) { 
  AsyncWebServerResponse *response = request->beginResponse(200);
    request->send_P(200, "text/html", index_html.c_str(), processor);
    });
*/



	//Receive post from settings site
	server.on("/", HTTP_POST, [](AsyncWebServerRequest* request) {
		int params = request->params();
		for (int i = 0;i < params;i++) {
			AsyncWebParameter* p = request->getParam(i);
			if (p->isFile()) { //p->isPost() is also true
				Serial.printf("FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
			}
			else if (p->isPost()) {

				
				Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
			}
			else {
				Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
			}
		} // for(int i=0;i<params;i++)

		Serial.println("config.json");
		File filec = SPIFFS.open("/config.json", FILE_WRITE);
		if (!filec) {
			Serial.println("There was an error opening the file /config.json for writing");
			return;
		}
		StaticJsonDocument<256> doc;
		if (request->hasArg("deposit_radios"))
		{
			AsyncWebParameter* p = request->getParam("deposit_radios", true);
			doc["deposit"] = p->value().c_str();
			Serial.println (0);
		}
		if (request->hasArg("price_alc"))
		{
			AsyncWebParameter* p = request->getParam("price_alc", true);
			doc["price_alc"] = p->value().c_str();
			Serial.println(1);
		}
		if (request->hasArg("price_nonalc"))
		{
			AsyncWebParameter* p = request->getParam("price_nonalc", true);
			doc["price_nonalc"] = p->value().c_str();
			Serial.println(2);
		}

		// Serialize JSON to file
		if (serializeJson(doc, filec) == 0) {
			Serial.println(F("Failed to write to file"));
		}
		else
		{
			Serial.println(F("File /config.json written"));
		}
		serializeJson(doc, Serial);



		filec.close();

		request->send(200, "text/html", index_html.c_str());
		}); // server.on
	/*
	server.on("/settings", HTTP_POST, [](AsyncWebServerRequest* request) {
		request->send(200, "text/plain", "Post route");
		});
	*/

	// Route to load style.css file
	server.on("/css/design.css", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, "/design.css", "text/css");
		});


	server.on("/css/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, "/bootstrap.min.css", "text/css");
		});

   server.onNotFound(notFound);

   
   //myStatus = ANZEIGE_WELCOME;
   myDisplay.displaycurrentStat(WELCOME);
   myLED.showLED(ANZEIGE_ERFOLG);
	 // xTaskCreate(Anzeige, "Anzeige", 5000, NULL, 1, NULL);
    xSemaphoreTake(xRFIDSemaphore, (TickType_t)10);
 
    Serial.println("Start");
    xTaskCreatePinnedToCore(RFID, "RFID", 10000, NULL, 1, NULL,0);
    //Start server
   server.begin();

   


}
void loop() 
{  

/* Beginn der UART Kommunikation */
/* 1. Erhalt der UART Nachricht
 * 2. Filtern der Nachrichten/ es kommen manchmal unsynchronisierte/ falsche Daten, die werden herraus gefiltert!
   3. Auslesen der Nachricht -> 8 Werte werden geschcikt(0 oder 1), die stehen für die einzelnen Getränkzutaten 1= es ist genügend da, 0= es ist zu wenig
   4. UART Array wird dem Auswertungsarray übergeben
   5. Informationen werden aus dem Auswertungsarray herrausgenommen und in einzelne Variablen gespeichtert( Grenadine, Wodka , Malibu etc.)
   6. Aufruf der Funktionen, um herauszufinden, ob einzelne Cocktails machbar sind oder nicht siehe functions.cpp, dies wird dann in ein alc-array/ non-alc-array gespeichtert

So viel zu dem Loop

Leertrinkbetrieb.h

statische Teil des empty-drink_mode

Leertrinkbetrieb.cpp

dynamische Teil, hier werden die zwei Arrays (alc-array und non-alc array mit einer if-Bedinung ausgelesen, um nur die möglichen Cocktails darzustellen

*/
if(Serial.available())
{
    /* rofa */
    if( Serial.read()== true)
      {
            getstarted= true;
            Serial.write(getstarted);

            for(int i=0; i<8; i++)
                {
                    //counter++;
                    incomingByte[i]= Serial.read();
                    //Serial.print(incomingByte[i]);
       
                }
            Serial.println();
                 /*
                 if (counter== 8)
                 {
                     getstarted= false;
                 }
                 */
                 
                 /* Filter */
                 
              for(int b=0; b<8; b++)
              {

                      if(incomingByte[b] == true)
                      {
                          counter2= counter2+1;
                      }
                      else 
                      {
                       // do nothing
                      }
              }
              
              if(counter2 == 8)
              {
                Serial.print(0);
              }
              else if(counter2 <8)
              {
              for(int b=0; b<8; b++)
              {
                auswertungs_array[b]=incomingByte[b];
               //Serial.print(incomingByte[b]);
              }
              }
              counter2=0;


              /* Start der Zuweisung */

              
              pointer_to_auswertungs_array=  auswertungs_array;
              if (*(pointer_to_auswertungs_array) == true)
              {
                  grenadine = true;
              }
              else
              {
                  grenadine = false;
              }
              Serial.println("Wert Grenadine:");
              Serial.println(grenadine);

              pointer_to_auswertungs_array++;

              if (*(pointer_to_auswertungs_array) == true)
              {
                   zitrone = true;
              }
              else
              {

              zitrone = false;
              }
              Serial.println("Wert Zitrone:");
              Serial.println(zitrone);

              pointer_to_auswertungs_array++;

              if (*(pointer_to_auswertungs_array) == true)
              {
                   wodka = true;
              }
              else
              {

              wodka = false;
              }
              Serial.println("Wert Wodka:");
              Serial.println(wodka);

              pointer_to_auswertungs_array++;

              if (*(pointer_to_auswertungs_array) == true)
              {
                   orange = true;
              }
              else
              {

              orange = false;
              }
              Serial.println("Wert Orange:");
              Serial.println(orange);

              pointer_to_auswertungs_array++;

              if (*(pointer_to_auswertungs_array) == true)
              {
                   maracuja = true;
              }
              else
              {

              maracuja = false;
              }
              Serial.println("Wert Maracuja:");
              Serial.println(maracuja);

              pointer_to_auswertungs_array++;

              if (*(pointer_to_auswertungs_array) == true)
              {
                   malibu = true;
              }
              else
              {

              malibu = false;
              }
              Serial.println("Wert Malibu:");
              Serial.println(malibu);

              pointer_to_auswertungs_array++;

              if (*(pointer_to_auswertungs_array) == true)
              {
                   ananas = true;
              }
              else
              {

              ananas = false;
              }
              Serial.println("Wert Ananas:");
              Serial.println(ananas);

              pointer_to_auswertungs_array++;

              if (*(pointer_to_auswertungs_array) == true)
              {
                   banane = true;
              }
              else
              {

              banane = false;
              }
              Serial.println("Wert Banane:");
              Serial.println(banane);


              /* Check all alcoholic cocktails*/

              // Alkoholische Getränke
              wodka_maracuja_1(wodka, maracuja);
              malibu_maracuja_2(malibu, maracuja);
              malibu_orange_3(malibu, orange);
              malibu_orange_grenadine_4(malibu, orange, grenadine);
              wodka_orange_5(wodka, orange);
              wodka_malibu_orange_6(wodka,malibu, orange);
              wodka_malibu_ananas_7(wodka, malibu, ananas);
              wodka_grenadine_ananas_8(wodka, grenadine, ananas);
              wodka_zitrone_9(wodka, zitrone);
              wodka_zitrone_maracuja_ananas_grenadine_banane_orange_10(wodka, zitrone, maracuja, ananas, grenadine, banane, orange);
              wodka_ananas_11(wodka, ananas);
              wodka_orange_12(wodka, orange);

              delay(1000);

              Serial.println("Alkoholische Liste an Cocktails:");
              for(int i=0; i<12;i++)
              {
                
                Serial.print(alcoholic_cocktails[i]);
              }
              Serial.println();

              // Antialkoholische Getränke

              maracuja_1(maracuja);
              orange_2(orange);
              maracuja_orange_ananas_zitrone_grenadine_3(maracuja, orange, ananas, zitrone, grenadine);
              banane_ananas_maracuja_grenadine_4(banane, ananas, maracuja, grenadine);
              zitrone_orange_5(zitrone, orange);
              grenadine_zitrone_orange_maracuja_ananas_6(grenadine, zitrone, orange, maracuja, ananas);
              zitrone_grenadine_orangensaft_ananas_7(zitrone, grenadine, orange, ananas);
              zitrone_grenadine_orange_maracuja_ananas_8(zitrone, grenadine, orange, maracuja, ananas);
              zitrone_grenadine_maracuja_orange_ananas_9(zitrone, grenadine, orange, maracuja, ananas);
              grenadine_zitrone_orange_banane_10(grenadine, zitrone, orange, banane);
              zitrone_grenadine_maracuja_ananas_11(zitrone, grenadine, maracuja, ananas);
              zitrone_grenadine_orange_maracuja_12(zitrone, grenadine, orange, maracuja);
              ananas_orange_13(ananas, orange);
              zitrone_orange_ananas_14(zitrone, orange, ananas);
              zitrone_orange_ananas_15(zitrone, orange, ananas);
              grenadine_orange_ananas_16(grenadine, orange, ananas);
              orange_maracuja_ananas_17(orange, maracuja,ananas);
              grenadine_orange_ananas_18(grenadine, orange, ananas);
              

              
              delay(1000);

              Serial.println("Anti-Alkoholische Liste an Cocktails:");
              for(int i=0; i<18;i++)
              {
                
                Serial.print(non_alcoholic_cocktails[i]);
              }
              

              

              

              /* rofa */
              

              
         

          
      }
   }

else
{
  delay(500);
}

  
  
  //}
    

    /* rofa */
}




/* War nur ein Experiment, hat aber nicht so funktioniert */
void justtrying()
{
    server.on("/Bestellung", HTTP_POST,
    [](AsyncWebServerRequest* request) {},
    NULL,
    [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total)
  {

      int ii;
      for (size_t i = 0; i < len; i++) 
      {
        myCocktail[i] = data[i];
        Serial.print(myCocktail[i]);
      }
     for(size_t i =len; i<32; i++)
     {
        myCocktail[i] = 0;
     }
   Serial.println();
   xSemaphoreGive(xAnzeigeSemaphore);
   oderReady = true;
   Serial.println("Bestellung Display");
   Serial.println("Bestellung fertig");
   xSemaphoreGive(xRFIDSemaphore);
   request->send(200);
    });
  }









 
    





  
     
