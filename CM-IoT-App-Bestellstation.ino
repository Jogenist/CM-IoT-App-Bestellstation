/*
Type:    Program
Date:   14.08.2019
Author:   Tim Schanz
Description:  The main program setup and loop. configureing and starting the async webserver. The files and contents are send to the client depending on the request. Configuration information are stored in a json file on SPIFFS. Data is transfered between configuration page and main page as a html post.
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
using namespace std;


#include "index.h"
#include "settings.h"
#include "Leertrinkbetrieb.h"
#include "CustomCocktails.h"
#include "bootstrap.min.css.h"
#include "design.css.h"
#include "JS.h"

const char* assid = "Xperia";
const char* apassword = "133713371337";

const char* cssid = "";
const char* cpassword = "";
//string html_head;
string index_html;
string settings_html;
string Leertrinkbetrieb_html;
string custom_html;
AsyncWebServer server(80);

RFID_Card myRFID;
DISPLAY_SSH1106 myDisplay;
LED myLED;
bool isAlc=false;
char myCocktail[32];
char * myCustomCocktail[8]; //jg0402
bool oderReady = false;
uint8_t myStatus = 0;
SemaphoreHandle_t xAnzeigeSemaphore = NULL;
SemaphoreHandle_t xRFIDSemaphore = NULL;
RFIDerrorcode Status;


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
  String price_custom;
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

    else if (var == "PLACEHOLDER_PRICE_CUSTOM") //cs:0402 -> ganze "else if" kopiert
    {
      return String(30);
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

    else if (var == "PLACEHOLDER_PRICE_CUSTOM")   //cs:0402 -> ganzen block kopiert
    {
      price_custom = doc["price_custom"].as<const char*>();
      return String(price_custom);
    }

    
  }
  return String();
}

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
    [](AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {

      int ii;
      for (size_t i = 0; i < len; i++) {
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
  //Favicon
  server.on("/image/favico.ico", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/favico.ico", "image/x-icon");
    });

  //Logo
  server.on("/image/hska_logo.png", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(SPIFFS, "/hska_logo.png", "image/png");
  });

  //Answer request for settings page
  settings_html.append(SETTINGS_page_Begin);
  settings_html.append(SETTINGS_page_After);
  server.on("/settings", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/html", settings_html.c_str());
    });

  //Answer request for custom page
  custom_html.append(CUSTOM_page_Begin);
  custom_html.append(CUSTOM_page_AfterFooter_BeforeScript);
  custom_html.append(JAVASCRIPT_static);
  custom_html.append(CUSTOM_page_AfterFooter_AfterScript);
  server.on("/custom", HTTP_GET, [](AsyncWebServerRequest* request) { 
  AsyncWebServerResponse *response = request->beginResponse(200);
    request->send_P(200, "text/html", custom_html.c_str(), processor);
    });


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

void loop() {
  //Serial.print("LOOP:\t");
  //Serial.println(xPortGetCoreID());
  //Serial.println(getCpuFrequencyMhz());
  delay(1000);
}
