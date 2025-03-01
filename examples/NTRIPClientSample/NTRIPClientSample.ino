/*
 *  NTRIP client for Arduino Ver. 1.0.0 
 *  NTRIPClient Sample
 *  Request Source Table (Source Table is basestation list in NTRIP Caster)
 *  Request Reference Data 
 * 
 * 
 */
//#include <ESP8266WiFi.h>  //Need for ESP8266
//#include <WiFi.h>           //Need for ESP32 
#include <WiFiNINA.h>
#include "NTRIPClient.h"

const char* ssid     = "your_ssid";
const char* password = "your_password";

char* host = "ntrip caster host";  // "rtk2go.com"
int httpPort = 2101; //port 2101 is default port of NTRIP caster
char* mntpnt = "ntrip caster's mountpoint"; // "AustinTexas"
char* user   = "ntrip caster's client user";
char* passwd = "ntrip caster's client password";
NTRIPClient ntrip_c;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000); //Sufficient delay to see something
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.println("Requesting SourceTable.");
  if(ntrip_c.reqSrcTbl(host,httpPort)){
    char buffer[512];
    delay(5);
    while(ntrip_c.available()){
      ntrip_c.readLine(buffer,sizeof(buffer));
      Serial.print(buffer); 
    }
  }
  else{
    Serial.println("SourceTable request error");
  }
  Serial.print("Requesting SourceTable is OK\n");
  ntrip_c.stop(); //Need to call "stop" function for next request.
  
  Serial.println("Requesting MountPoint's Raw data");
  if(!ntrip_c.reqRaw(host,httpPort,mntpnt,user,passwd)){
    delay(15000);
    //ESP.restart();
  }
  Serial.println("Requesting MountPoint is OK");

  
}

void loop() {
  // put your main code here, to run repeatedly:
  while(ntrip_c.available()) {
        char ch = ntrip_c.read();        
        Serial.print(ch);
        
  }
}
