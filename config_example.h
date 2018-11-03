///////////////////////////// config /////////////////////////////
// Lamp
const int    lamp           = 1;              // 0 = turn off pixels by default, 1 = set color to "orange" after bootup

// Network
const char*  ssid           = "YourSSID";
const char*  password       = "yourPassword";
const int    localUdpPort   = 2342;
char         incomingPacket[255];
unsigned int wlanTimeout    = 60;           // seconds to try for WLAN connection

// OTA
const int    OTAUpdate      = 1;              // 0 = disable OTA, 1 = enable OTA
const char*  OTAHostname    = "lamp01";
const char*  OTAPassword    = "yourOTAPassword";
const int    OTAPort        = 8266;

// neopixel
const int NUMPIXELS         = 60;
const int LEDPIN1           = 15;
const int LEDPIN2           = 14;

// defaults
unsigned int baudRate       = 115200;
unsigned int displayRefresh = 10;
unsigned int debugMode      = 0;             // 0 = off, 1 = on
