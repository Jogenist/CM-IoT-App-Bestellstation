
#include "Ambient.h"
//includes to use ESP_NOW: 
#include "esp_now.h"
#include "WiFi.h"
//#include "Configuration.h"

#define NUMSLAVES 2    //Anzahl der Slaves 3: Füllstand, LED und Bedienpanel
#define CHANNEL 6
#define PRINTSCANRESULTS 0




//extern uint8_t* receivedData; // Pointer to stock
//extern uint16_t stock[8];       //Füllstand

void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status);   // callback (automatically) when data is sent from Master to Slave
void OnDataRecv(const uint8_t* mac_addr, const uint8_t* pdata, int data_len);   //callback (automatically) when data is received from Füllstands - Slave

class cWifiESPNow
{
public:
  cWifiESPNow();
  void Init();    // Init ESP Now with fallback
  void ScanForSlave();    // Scan for slaves in AP mode
  void manageSlave();   // Check if the slave is already paired with the master If not, pair the slave with master
  bool requestStock();  //Request Füllstand, by sending 99 to Stock-ESP
  bool requestorderpanel(); //Request Bedienpanel, by sending 99 to Stock-ESP
  bool sendUserInfo(byte led);  //Send Userinformation to LED ESP
  bool recFlag = false; // Flag set by OnDataRecv when answer from stock ESP32 has been received --> has to be public
private:
  int mSlaveCnt;
  esp_now_peer_info_t slaves[NUMSLAVES];
};
