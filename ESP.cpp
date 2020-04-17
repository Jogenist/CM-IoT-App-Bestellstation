#include "ESPnow.h"


uint16_t stock[8]={0};
//bool recFlag=false; 
cWifiESPNow::cWifiESPNow()
{
  mSlaveCnt = 0;
}

// Init ESP Now with fallback
void cWifiESPNow::Init()
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
//#ifdef SERIAL_DEBUG
    Serial.println("ESPNow Init Success");
//#endif
  }
  else {
//#ifdef SERIAL_DEBUG
    Serial.println("ESPNow Init Failed");
//#endif
    // Retry InitESPNow, add a counte and then restart?
    // InitESPNow();
    // or Simply Restart
    ESP.restart();
  }
//#ifdef SERIAL_DEBUG
  Serial.print("Wifi Mixing Unit MAC-Adress: "); Serial.println(WiFi.macAddress());
//#endif
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
};

// Scan for slaves in AP mode
void cWifiESPNow::ScanForSlave() {
  int8_t scanResults = WiFi.scanNetworks();
  //reset slaves
  memset(slaves, 0, sizeof(slaves));
  mSlaveCnt = 0;
  Serial.println("");
  if (scanResults == 0) {
//#ifdef SERIAL_DEBUG
    Serial.println("No WiFi devices in AP Mode found");
//#endif
  }
  else {
//#ifdef SERIAL_DEBUG
    Serial.print("Found "); Serial.print(scanResults); Serial.println(" devices ");
//#endif
    for (int i = 0; i < scanResults; ++i) {
      // Print SSID and RSSI for each device found
      String SSID = WiFi.SSID(i);
      int32_t RSSI = WiFi.RSSI(i);
      String BSSIDstr = WiFi.BSSIDstr(i);

      if (PRINTSCANRESULTS) {
        Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
      }
      delay(10);
      // Check if the current device starts with `Slave`
      if (SSID.indexOf("CmIoTSlave") == 0) {
        // SSID of interest
        Serial.print(i + 1); Serial.print(": "); Serial.print(SSID); Serial.print(" ["); Serial.print(BSSIDstr); Serial.print("]"); Serial.print(" ("); Serial.print(RSSI); Serial.print(")"); Serial.println("");
        // Get BSSID => Mac Address of the Slave
        int mac[6];

        if (6 == sscanf(BSSIDstr.c_str(), "%x:%x:%x:%x:%x:%x%c", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5])) {
          for (int ii = 0; ii < 6; ++ii) {
            slaves[mSlaveCnt].peer_addr[ii] = (uint8_t)mac[ii];
          }
        }
        slaves[mSlaveCnt].channel = CHANNEL; // pick a channel
        slaves[mSlaveCnt].encrypt = 0; // no encryption
        mSlaveCnt++;
      }
    }
  }
  if (mSlaveCnt > 0) {
//#ifdef SERIAL_DEBUG
    Serial.print(mSlaveCnt); Serial.println(" Slave(s) found, processing..");
//#endif
  }
  else {
//#ifdef SERIAL_DEBUG
    Serial.println("No Slave Found with Prefix CmIoTSlave");
//#endif
  }

  // clean up ram
  WiFi.scanDelete();
}

// Check if the slave is already paired with the master.
// If not, pair the slave with master
void cWifiESPNow::manageSlave() {
  if (mSlaveCnt > 0) {
    for (int i = 0; i < mSlaveCnt; i++) {
      const esp_now_peer_info_t* peer = &slaves[i];
      const uint8_t* peer_addr = slaves[i].peer_addr;
//#ifdef SERIAL_DEBUG
      Serial.print("Processing: ");
      for (int ii = 0; ii < 6; ++ii) {
        Serial.print((uint8_t)slaves[i].peer_addr[ii], HEX);
        if (ii != 5) Serial.print(":");
      }
//#endif
      //Debug informations: Status
//#ifdef SERIAL_DEBUG
      Serial.print(" Status: ");
//#endif
      // check if the peer exists
      bool exists = esp_now_is_peer_exist(peer_addr);
      if (exists) {
        // Slave already paired.
//#ifdef SERIAL_DEBUG
        Serial.println("Already Paired");
//#endif
      }
      else {
        // Slave not paired, attempt pair
        esp_err_t addStatus = esp_now_add_peer(peer);     //Pairing of Devices
//#ifdef SERIAL_DEBUG
        if (addStatus == ESP_OK) {
          // Pair success
          Serial.println("Pair success");                 //Serial print of failures:
        }
        else if (addStatus == ESP_ERR_ESPNOW_NOT_INIT) {
          // How did we get so far!!
          Serial.println("ESPNOW Not Init");
        }
        else if (addStatus == ESP_ERR_ESPNOW_ARG) {
          Serial.println("Add Peer - Invalid Argument");
        }
        else if (addStatus == ESP_ERR_ESPNOW_FULL) {
          Serial.println("Peer list full");
        }
        else if (addStatus == ESP_ERR_ESPNOW_NO_MEM) {
          Serial.println("Out of memory");
        }
        else if (addStatus == ESP_ERR_ESPNOW_EXIST) {
          Serial.println("Peer Exists");
        }
        else {
          Serial.println("Not sure what happened");
        }
//#endif
        delay(100);
      }
    }
  }
  else {
    // No slave found to process
//#ifdef SERIAL_DEBUG
    Serial.println("No Slave found to process");
//#endif
  }
}


// send data to LED device
bool cWifiESPNow::sendUserInfo(byte led) {

  ScanForSlave();
  if (mSlaveCnt > 0) { // check if slave channel is defined
    manageSlave();

    for (int i = 0; i < mSlaveCnt; i++) {                 //Send data to ALL Slaves
      const uint8_t* peer_addr = slaves[i].peer_addr;                     //necessary cast
      if (i == 0) {                           // print only for first slave
//#ifdef SERIAL_DEBUG
        Serial.print("Sending: ");
        Serial.println(led);
//#endif
      }
      esp_err_t result = esp_now_send(peer_addr, &led, sizeof(led));    //send data 

      //Debug informations Send Status: 
//#ifdef SERIAL_DEBUG
      Serial.print("Send Status: ");
//#endif
      if (result == ESP_OK)
      {
//#ifdef SERIAL_DEBUG
        Serial.println("Success");
//#endif
        return (true);
      }
//#ifdef SERIAL_DEBUG
      else if (result == ESP_ERR_ESPNOW_NOT_INIT)
        Serial.println("ESPNOW not Init.");
      else if (result == ESP_ERR_ESPNOW_ARG)
        Serial.println("Invalid Argument");
      else if (result == ESP_ERR_ESPNOW_INTERNAL)
        Serial.println("Internal Error");
      else if (result == ESP_ERR_ESPNOW_NO_MEM)
        Serial.println("ESP_ERR_ESPNOW_NO_MEM");
      else if (result == ESP_ERR_ESPNOW_NOT_FOUND)
        Serial.println("Peer not found.");
      else
        Serial.println("Not sure what happened");
//#endif
      return(false);
    }
  }
  else
  {
//#ifdef SERIAL_DEBUG
    Serial.println("No Slave found");
//#endif
    return (false);
  }
}

//Füllstand anfragen 
bool cWifiESPNow::requestStock()
{

      uint16_t count = 0;   // used to count time from request to received data
                // BESSER MIT millis() INTEGRIEREN???
      //ScanForSlave();   // search for all devices in AP mode with Prefix "CmIoTSlave"


      if (mSlaveCnt > 0) //&&(request==88)) // activating request in html whatever
      
      {       // if slave had been found during last scan...
              //manageSlave();

              byte request = 88;                    // set by button click/action 

              for (int i = 0; i < mSlaveCnt; i++) 
              {
                   const uint8_t* peer_addr = slaves[i].peer_addr;     //necessary cast
                   //#ifdef SERIAL_DEBUG
                   
                   if (i == 0) 
                   { 
                      // print only for first slave
                        Serial.print("Sending: ");
                        Serial.println(request);
                   }
                   
                 // #endif
              
                   esp_err_t result = esp_now_send(peer_addr, &request, sizeof(request));    //send data 

                  //Debug informations Send Status: 
                  // #ifdef SERIAL_DEBUG
                   Serial.print("Send Status: ");
                  // #endif
              
                   if (result == ESP_OK)
                      {
                           // #ifdef SERIAL_DEBUG
                            Serial.println("Success");
                            //#endif
                            
                            while (!recFlag)    // wait until receiveFlag has been set by receive interrupt routine
                            {   // hier Timeout integrieren
                              
                                if (count < 1000)
                                {
                                    count++;
                                }
                      
                                else
                                {
                                    //#ifdef SERIAL_DEBUG
                                    Serial.println("Timeout while waiting for answer from stock esp32");
                                    //#endif
                                    return false; // return error
                                } 
                                delay(1);
                            }// while-Schleife

            
                            //#ifdef SERIAL_DEBUG
                            for (int i = 0; i < 8; i++)
                            {
                             Serial.printf("Received Stock %d: %d\n", i, stock[i]);
                            }
                            
                            Serial.printf("Time Waited for Answer %d ms\n", count);
//                            #endif
                 
                            recFlag = false;  // reset recFlag
                            return (true);
     
      
      
      
                    }// if(result==ESP_ok)


      
                // #ifdef SERIAL_DEBUG
                 else if (result == ESP_ERR_ESPNOW_NOT_INIT)
                 Serial.println("ESPNOW not Init.");
                 else if (result == ESP_ERR_ESPNOW_ARG)
                Serial.println("Invalid Argument");
                else if (result == ESP_ERR_ESPNOW_INTERNAL)
                Serial.println("Internal Error");
                else if (result == ESP_ERR_ESPNOW_NO_MEM)
                Serial.println("ESP_ERR_ESPNOW_NO_MEM");
                else if (result == ESP_ERR_ESPNOW_NOT_FOUND)
                 Serial.println("Peer not found.");
                else
                Serial.println("Not sure what happened");
              //  #endif
                delay(100);
                return (false);
                
    }// Ende for-Schleife
  }



  
  else  // if no slaves have been found during last scan...
        {
            //#ifdef SERIAL_DEBUG
            Serial.println("No Slave found to request stock");
           // #endif
            return (false);
        }
}

 




// callback (automatically) when data is sent from Master to Slave
void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
  char macStr[18];
//#ifdef SERIAL_DEBUG
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
    mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Last Packet Sent to: "); Serial.println(macStr);
  Serial.print("Last Packet Send Status: "); Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
//#endif
}

//callback (automatically) when data is received from Füllstands - Slave 
void OnDataRecv(const uint8_t* mac_addr, const uint8_t* pdata, int data_len)
{ 
  uint16_t stock[8]={0};
  cWifiESPNow wifiCom;   // object of this class included to have access to recFlag
  uint8_t* receivedData = (uint8_t*)stock;    // Local Pointer on Stock Array (Füllstand)

  char macStr[18];
//  Serial print Mac-Adress of Slave
//#ifdef SERIAL_DEBUG
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
    mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
//#endif
  for (int i = 0; i < 16; i++)     // ursprünglich 16, warum nicht 8(versuch es mal) 
  {
    receivedData[i] = pdata[i];       //Copy received Data into receivedData-Array (= Stock-Array)
  }
  wifiCom.recFlag = true;   // set receive Flag, to allow following actions in requestStock()-Method
   // recFlag= true;

for(int i=0; i<8; i++)
{
 
  Serial.println("Ausgabe der Werte: ");
  Serial.println(stock[i]);
  
}



  //For Debugging: 
//#ifdef SERIAL_DEBUG
  Serial.print("Last Packet Recv from: "); Serial.println(macStr);
  Serial.println("Last Packet Recv Data copied into Stock-Variable: ");
//#endif
}
