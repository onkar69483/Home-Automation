// Uncomment the following line to enable serial debug output
//#define ENABLE_DEBUG
#ifdef ENABLE_DEBUG
 #define DEBUG_ESP_PORT Serial
 #define NODEBUG_WEBSOCKETS
 #define NDEBUG
#endif 
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "SinricPro.h"
#include "SinricProSwitch.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <map>

#define WIFI_SSID "SSID" 
#define WIFI_PASS "your_password"
#define APP_KEY "bfcbe46d-4d6d-445e-b76c" //your_app key
#define APP_SECRET "e7dc6ae8-703e-4017-82c2-18fcc2a58e5d-64c00738-a8c2-4d3a-9dc9" // Replace with your app secret key
#define BOTtoken "5651849401:AAEdhpyEUdbYx8Wx9pxgJvFJBHE" //Replace with your Telegram Bot Token
#define CHAT_ID "10934" //Replace with you telegram chat Id
  
X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int const trigPin = 12 ; //D6
int const echoPin = 13; //D7
int const buzzPin = 15; //D8
const int LED1 = 3; //RX
int flamesensor = 1;//TX
int flame = LOW ;
//Enter the device IDs here
#define device_ID_1 "638c2560b8a7fefbd656"
#define device_ID_2 "638c2546b8a7fefbd653"
#define device_ID_3 "638c2358b8a7fefbd65"
// define the GPIO connected with Relays and switches
#define RelayPin1 5 //D1
#define RelayPin2 4 //D2
#define RelayPin3 14 //D5
#define SwitchPin1 10 //SD3
#define SwitchPin2 0 //D3 
#define SwitchPin3 9 //SD2
#define wifiLed 16 //D0
// comment the following line if you use a toggle switches instead of tactile buttons
//#define TACTILE_BUTTON 1
#define BAUD_RATE 115200
#define DEBOUNCE_TIME 250
typedef struct { // struct for the std::map below
 int relayPIN;
 int flipSwitchPIN;
} deviceConfig_t;
// this is the main configuration
// please put in your deviceId, the PIN for Relay and PIN for flipSwitch
// this can be up to N devices...depending on how much pin's available on your device ;)
// right now we have 4 devicesIds going to 4 relays and 4 flip switches to switch the relay manually
std::map<String, deviceConfig_t> devices = {
 //{deviceId, {relayPIN, flipSwitchPIN}}
 {device_ID_1, { RelayPin1, SwitchPin1 }},
 {device_ID_2, { RelayPin2, SwitchPin2 }},
 {device_ID_3, { RelayPin3, SwitchPin3 }}
 };
typedef struct { // struct for the std::map below
 String deviceId;
 bool lastFlipSwitchState;
 unsigned long lastFlipSwitchChange;
} flipSwitchConfig_t;
std::map<int, flipSwitchConfig_t> flipSwitches; // this map is used to map flipSwitch PINs to deviceId and 
handling debounce and last flipSwitch state checks
 // it will be setup in "setupFlipSwitches" function, using informations from 
devices map
void setupRelays() { 
 for (auto &device : devices) { // for each device (relay, flipSwitch combination)
 int relayPIN = device.second.relayPIN; // get the relay pin
 pinMode(relayPIN, OUTPUT); // set relay pin to OUTPUT
 digitalWrite(relayPIN, LOW);
 }
}
void setupFlipSwitches() {
 for (auto &device : devices) { // for each device (relay / flipSwitch combination)
 flipSwitchConfig_t flipSwitchConfig; // create a new flipSwitch configuration
 flipSwitchConfig.deviceId = device.first; // set the deviceId
 flipSwitchConfig.lastFlipSwitchChange = 0; // set debounce time
 flipSwitchConfig.lastFlipSwitchState = true; // set lastFlipSwitchState to false (LOW)--
 int flipSwitchPIN = device.second.flipSwitchPIN; // get the flipSwitchPIN
 flipSwitches[flipSwitchPIN] = flipSwitchConfig; // save the flipSwitch config to flipSwitches map
 pinMode(flipSwitchPIN, INPUT_PULLUP); // set the flipSwitch pin to INPUT
 }
}
bool onPowerState(String deviceId, bool &state)
{
 Serial.printf("%s: %s\r\n", deviceId.c_str(), state ? "on" : "off");
 int relayPIN = devices[deviceId].relayPIN; // get the relay pin for corresponding device
 digitalWrite(relayPIN, state); // set the new relay state
 return true;
}
void handleFlipSwitches() {
 unsigned long actualMillis = millis(); // get actual millis
 for (auto &flipSwitch : flipSwitches) { // for each flipSwitch in flipSwitches map
 unsigned long lastFlipSwitchChange = flipSwitch.second.lastFlipSwitchChange; // get the timestamp 
when flipSwitch was pressed last time (used to debounce / limit events)
 if (actualMillis - lastFlipSwitchChange > DEBOUNCE_TIME) { // if time is > debounce time...
 int flipSwitchPIN = flipSwitch.first; // get the flipSwitch pin from configuration
 bool lastFlipSwitchState = flipSwitch.second.lastFlipSwitchState; // get the lastFlipSwitchState
 bool flipSwitchState = digitalRead(flipSwitchPIN); // read the current flipSwitch state
 if (flipSwitchState != lastFlipSwitchState) { // if the flipSwitchState has changed...
#ifdef TACTILE_BUTTON
 if (flipSwitchState) { // if the tactile button is pressed 
#endif 
 flipSwitch.second.lastFlipSwitchChange = actualMillis; // update lastFlipSwitchChange time
 String deviceId = flipSwitch.second.deviceId; // get the deviceId from config
 int relayPIN = devices[deviceId].relayPIN; // get the relayPIN from config
 bool newRelayState = !digitalRead(relayPIN); // set the new relay State
 digitalWrite(relayPIN, !newRelayState); // set the trelay to the new state
 SinricProSwitch &mySwitch = SinricPro[deviceId]; // get Switch device from SinricPro
 mySwitch.sendPowerStateEvent(newRelayState); // send the event
#ifdef TACTILE_BUTTON
 }
#endif 
 flipSwitch.second.lastFlipSwitchState = flipSwitchState; // update lastFlipSwitchState
 }
 }
 }
}
void setupWiFi()
{
 Serial.printf("\r\n[Wifi]: Connecting");
 WiFi.begin(WIFI_SSID, WIFI_PASS);
 while (WiFi.status() != WL_CONNECTED)
 {
 Serial.printf(".");
 delay(250);
 }
 digitalWrite(wifiLed, LOW);
 Serial.printf("connected!\r\n[WiFi]: IP-Address is %s\r\n", WiFi.localIP().toString().c_str());
}
void setupSinricPro()
{
 for (auto &device : devices)
 {
 const char *deviceId = device.first.c_str();
 SinricProSwitch &mySwitch = SinricPro[deviceId];
 mySwitch.onPowerState(onPowerState);
 }
 SinricPro.begin(APP_KEY, APP_SECRET);
 SinricPro.restoreDeviceStates(true);
}
void setup()
{
 Serial.begin(BAUD_RATE);
 configTime(0, 0, "pool.ntp.org"); 
 client.setTrustAnchors(&cert);
 pinMode(wifiLed, OUTPUT);
 digitalWrite(wifiLed, HIGH);
 pinMode(trigPin, OUTPUT); 
 pinMode(echoPin, INPUT);
 pinMode(buzzPin, OUTPUT);
 pinMode(LED1 , OUTPUT);
 pinMode(flamesensor, INPUT);
 
 setupRelays();
 setupFlipSwitches();
 setupWiFi();
 setupSinricPro();
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
 bot.sendMessage(CHAT_ID, "Wifi Connected!", "");
 bot.sendMessage(CHAT_ID, "System has Started!!", "");
}
void checkbot()
{
 bot.sendMessage(CHAT_ID, "loop is working!", "");
}
void loop()
{
 int duration, distance;
digitalWrite(trigPin, HIGH);
delay(1);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
if (distance <= 10 && distance >= 0) {
digitalWrite(buzzPin, HIGH);
digitalWrite(LED1, HIGH);
bot.sendMessage(CHAT_ID, "ALERT! MOTION D-ETECTED!!", "");
} 
else {
digitalWrite(buzzPin, LOW);
digitalWrite(LED1, LOW);
}
flame = digitalRead(flamesensor);
 if (flame == HIGH) {
 Serial.println( " fire occured please be safe");
 digitalWrite(LED1,HIGH);
 digitalWrite(buzzPin, HIGH);
 delay (100);
 }
 else{
 digitalWrite(LED1,LOW);
 digitalWrite(buzzPin, LOW);
 delay (100); 
 }
 SinricPro.handle();
 handleFlipSwitches();
}
