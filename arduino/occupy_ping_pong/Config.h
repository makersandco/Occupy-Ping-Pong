#ifndef __CONFIG_H__
#define __CONFIG_H__

// Wifi parameters
char* passphrase   = "ENTER PASSPHRASE";
char* ssid         = "ENTER SSID";
// occupy ping pong server
char* HOST         = "YOUR SERVER";
char* USERAGENT    = "occupy-ping-pong/alpha";
char* RESOURCE     = "/status.json";
//io settings
byte pirPin               = 2;   // infrared sensor pin 
byte ledPin               = 9;   // led pin
//misc
byte calibrationTime      = 15;
long unsigned int pause   = 1000;

#endif
