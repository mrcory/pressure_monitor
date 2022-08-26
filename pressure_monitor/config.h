//Sensor Read Pin
#define sensePin A0

//HA MQTT Broker Settings
#define brokerAddress IPAddress(192,168,254,84)
#define brokerUser ""
#define brokerPass ""

//A unique mac address
byte mac[] = {0x00, 0x10, 0xF2, 0x6E, 0xB8, 0x7A}; 

//Number of reading array positions
#define arraySize 10

//How often to get new value for pressure (milliseconds)
#define refreshTime 1000

//Minimum pressure before reading above 0
#define minimumThreshold 8

//Conversion Values
#define pressureMaxPSI 150
#define pressureMinPSI 0

//Values to map
#define pressureMaxVal 1024
#define pressureMinVal 200

//Wifi Settings
const char* ssid = "dd-wrt";
const char* password = "";

//Device Settings
#define myName "Pressure Monitor"

//Enable Serial Output
#define enableSerial
