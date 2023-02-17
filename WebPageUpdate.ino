// Temp Sensor:
  // Yellow:  D4

// Hall Sensors:
  //Sensor1:
    // Brown: (Data):     D12
  //Sensor2: 
    // Orange: (Data):    D14

// Relay Switch:
  // Pruple: (Control)  D130

#include <WiFi.h>       // standard library
#include <WebServer.h>  // standard library
#include "SuperMon.h"   // .h file that stores your html page code
#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>

DeviceAddress freezer = { 0x28, 0xFF, 0xA3, 0x4E, 0x62, 0x16, 0x3, 0x8E };
DeviceAddress garage = { 0x28, 0xFF, 0x33, 0xC4, 0x50, 0x16, 0x4, 0xE9 };
DeviceAddress outside = { 0x28, 0xFF, 0xA7, 0x98, 0x61, 0x16, 0x4, 0xFE };

// replace this with your homes intranet connect parameters
#define LOCAL_SSID "*************"
#define LOCAL_PASS "*************"

// start your defines for pins for sensors, outputs etc.
#define PIN_OUTPUT 26     // connected to nothing but an example of a digital write from the web page
#define PIN_TEMP 4          // some analog input sensor
#define PIN_HALL_C 12     // Hall Effect Sensor when Garage is closed
#define PIN_HALL_O 14     // Hall Effect Sensor when Garage is open
#define PIN_RELAY 13      // Relay Control
#define PIN_R_POW 32      // Provide Power to the  Relay Switch

OneWire oneWire (PIN_TEMP);
DallasTemperature sensors(&oneWire);

// variables to store measure data and sensor states
int BitsA0 = 0, BitsA1 = 0;                                 // Legacy - Maybe remove?
float VoltsA0 = 0, VoltsA1 = 0, tempFreezer = 0, tempGarage = 0, tempOutside = 0;                   // Legacy - Maybe remove  "VoltsA0 = 0, VoltsA1 = 0"  ?
int FanSpeed = 0;                                           // Legacy - Maybe remove?
bool LED0 = false, RelaySwitch = false, BitsHC = false, BitsHO = false;      // Legacy - maybe remove LED0?
uint32_t SensorUpdate = 0;
int FanRPM = 0;                                             // Legacy - Maybe remove?

// the XML array size needs to be bigger that your maximum expected size. 2048 is way too big for this example
char XML[2048];

// just some buffer holder for char operations
char buf[32];

// variable for the IP reported when you connect to your homes intranet (during debug mode)
IPAddress Actual_IP;

// definitions of your desired intranet created by the ESP32
IPAddress ip;

// gotta create a server
WebServer server(80);

void setup() {

  // standard stuff here
  Serial.begin(115200);

  //pinMode(PIN_FAN, OUTPUT);                                           // Legacy - Maybe remove?
  //pinMode(PIN_LED, OUTPUT);                                           // Legacy - Maybe remove?

  pinMode(PIN_RELAY, OUTPUT);
  
  // Set Data IN pins for Hall Sensors
  pinMode(PIN_HALL_C, INPUT);  // Set the pin for the hall effect sensor as an input
  pinMode(PIN_HALL_O, INPUT);  // Set the pin for the hall effect sensor as an input
  
  disableCore0WDT();

  // maybe disable watch dog timer 1 if needed
  //  disableCore1WDT();

  // just an update to progress
  Serial.println("starting server");

  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  Actual_IP = WiFi.localIP();

  //printWifiStatus();

  server.on("/", SendWebsite);

  server.on("/xml", SendXML);

  server.on("/BUTTON", ProcessButton);

  // finally begin the server
  server.begin();

}

void loop() {

  if ((millis() - SensorUpdate) >= 1000) {
    //Serial.println("Reading Sensors");
    SensorUpdate = millis();
    //BitsA0 = analogRead(PIN_A0);                  //remove?
    //BitsA1 = analogRead(PIN_A1);                  //remove?
    BitsHC = digitalRead(PIN_HALL_C);
    BitsHO = digitalRead(PIN_HALL_O);
    

    // temperature
  //Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");
  
  //Serial.print("Freezer: ");
    tempFreezer = sensors.getTempC(freezer); 
 
  //Serial.print("Garage: ");
    tempGarage = sensors.getTempC(garage); 
  
  //Serial.print("Outside: ");
    tempOutside = sensors.getTempC(outside); 

      // byte i;
      // byte present = 0;
      // byte type_s;
      // byte data[9];
      // byte addr[8];
      // float celsius;
      
      // if ( !ds.search(addr)) {
      //   ds.reset_search();
      //   delay(250);
      //   return;
      // }

      // if (OneWire::crc8(addr, 7) != addr[7]) {
      //     Serial.println("CRC is not valid!");
      //     return;
      // }
      // type_s = 0;
      
      // ds.reset();
      // ds.select(addr);
      // ds.write(0x44, 1);
        
      // present = ds.reset();
      // ds.select(addr);    
      // ds.write(0xBE);

      // for ( i = 0; i < 9; i++) {
      //   data[i] = ds.read();
      // }

      // int16_t raw = (data[1] << 8) | data[0];
      // if (type_s) {
      //   raw = raw << 3; 
      //   if (data[7] == 0x10) {
      //     raw = (raw & 0xFFF0) + 12 - data[6];
      //   }
      // } else {
      //   byte cfg = (data[4] & 0x60);
      //   if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
      //   else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
      //   else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
      // }
      // //celsius = (float)raw / 16.0;
      // TempD4 = (float)raw / 16.0;


  }

  server.handleClient();

delay(1000);

}


void ProcessButton() {

  // just a simple way to toggle a LED on/off. Much better ways to do this
  RelaySwitch = !RelaySwitch;
  digitalWrite(PIN_RELAY, RelaySwitch);
  
 // Serial.print("RelaySwitch: ");
 // Serial.println(RelaySwitch);
  
  delay(200);
  
  RelaySwitch = !RelaySwitch;
  digitalWrite(PIN_RELAY, RelaySwitch);
  
  //Serial.print("RelaySwitch: ");
  //Serial.println(RelaySwitch);

  server.send(200, "text/plain", ""); //Send web page

}


// code to send the main web page
// PAGE_MAIN is a large char defined in SuperMon.h
void SendWebsite() {

  server.send(200, "text/html", PAGE_MAIN);

}

// code to send the main web page
// I avoid string data types at all cost hence all the char mainipulation code
void SendXML() {

  // Serial.println("sending xml");

  strcpy(XML, "<?xml version = '1.0' encoding='UTF-8'?>\n<Data>\n");

  // send bits1
  sprintf(buf, "<B1>%d</B1>\n", BitsA1);
  strcat(XML, buf);
  // send Volts1                                                                                                                    //remove?
  sprintf(buf, "<V1>%d.%d</V1>\n", (int) (VoltsA1), abs((int) (VoltsA1 * 10)  - ((int) (VoltsA1) * 10)));                           //remove?
  strcat(XML, buf);                                                                                                                 //remove?


  if (RelaySwitch) {
    strcat(XML, "<RELAY>1</RELAY>\n");
  }
  else {
    strcat(XML, "<RELAY>0</RELAY>\n");
  }

  // show temp
  sprintf(buf, "<TF>%d.%d</TF>\n", (int) (tempFreezer), abs((int) (tempFreezer * 10)  - ((int) (tempFreezer) * 10)));
  strcat(XML, buf);
  sprintf(buf, "<TG>%d.%d</TG>\n", (int) (tempGarage), abs((int) (tempGarage * 10)  - ((int) (tempGarage) * 10)));
  strcat(XML, buf);
  sprintf(buf, "<TO>%d.%d</TO>\n", (int) (tempOutside), abs((int) (tempOutside * 10)  - ((int) (tempOutside) * 10)));
  strcat(XML, buf);

  // Hall sensors
  if (BitsHC){
    if (BitsHO) {
      strcat(XML, "<G0>Ajar</G0>\n");
    } 
    else {
      strcat(XML, "<G0>Open</G0>\n");
    } 
  }
  else {
    strcat(XML, "<G0>Closed</G0>\n");
  }

  strcat(XML, "</Data>\n");
  // wanna see what the XML code looks like?
  // actually print it to the serial monitor and use some text editor to get the size
  // then pad and adjust char XML[2048]; above
  //Serial.println(XML);

  server.send(200, "text/xml", XML);

}

// I think I got this code from the wifi example
// void printWifiStatus() {

//   // print the SSID of the network you're attached to:
//   Serial.print("SSID: ");
//   Serial.println(WiFi.SSID());

//   // print your WiFi shield's IP address:
//   ip = WiFi.localIP();
//   Serial.print("IP Address: ");
//   Serial.println(ip);

//   // print the received signal strength:
//   long rssi = WiFi.RSSI();
//   Serial.print("signal strength (RSSI):");
//   Serial.print(rssi);
//   Serial.println(" dBm");
//   // print where to go in a browser:
//   Serial.print("Open http://");
//   Serial.println(ip);
// }

// end of code
