#include "WiFly.h"
#include "Config.h"

/*
*
* occupy ping pong
*
* sven kraeuter for makers & co. and miami ad school europe
*
* http://makersand.co
*
* code inspired by http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1287148367
*
* wifly library for arduino 1.0: https://github.com/timr/WiFly-Shield
*
*/

byte motionCounter = 0;

Client client(HOST, 80);

void setup(){
  //------------------------ wifly setup ----------------------------------
  Serial.begin(9600);
  
  WiFly.begin();
  
  if (WiFly.join(ssid, passphrase)) {
    Serial.println("associted with wifly network.");
  } 
  else {
    Serial.println("Association failed.");
    while (1) {
      // Hang on failure.
    }
  }  
  
  //------------------------------ epir setup ----------------------------
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);  

  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}

void loop(){
//  //------------------- ePIR sensor part ---------------------------------------
//  if(digitalRead(pirPin) == HIGH){
//    Serial.println("Continuous motion ended.");
//    motionCounter = 0;
//    //--------- send status to server
//    connectClient(generateHttpPut(HOST, RESOURCE, '0'));
//    Serial.println();
//    Serial.println("disconnecting.");
//    client.stop();
//  }
//  else if(digitalRead(pirPin) == LOW){
//    motionCounter += 1;  
//    Serial.print("Single motion detected ");
//    Serial.print(motionCounter);
//    Serial.println(" times in a row.");
//  }
//  if(motionCounter > 4){
//    Serial.println("Continuous motion detected!");
//    //--------- send status to server 
//    connectClient(generateHttpPut(HOST, RESOURCE, '1'));
//    Serial.println();
//    Serial.println("disconnecting.");
//    client.stop();
//  }
  
  //-------------------- signalling led part -------------------------------------
  char postString[255];
  sprintf(postString, "GET http://%s%s HTTP/1.0\r\n", HOST, RESOURCE);
  connectClient(postString);
  
  if (client.available()) {
    // receiving status from server
    if(client.find("\"occupied\": ")){
      char state[1];
      client.readBytes(state, 1);
      Serial.println(state);
      if(atoi(state) == 1){
        Serial.println("PING PONG OCCUPIED!");
        digitalWrite(ledPin, HIGH);
      }
      else if(atoi(state) == 0) {
        Serial.println("PING PONG VACANT");
        digitalWrite(ledPin, LOW);
      }
    } 
    if (!client.connected()) {
      Serial.println();
      Serial.println("disconnecting.");
      client.stop();
    }
    
  }
  
  
  delay(pause); 
}

char* generateHttpPut(char* host, char* resource, char occupied){
  char postString[255];
  sprintf(postString, "PUT %s HTTP/1.1\r\nUser-Agent: %s\r\nHost: %s\r\nContent-Length: 15\r\nContent-Type: application/json\r\n\r\n{\"occupied\": %c}"
  , resource, USERAGENT, host, occupied);

  return postString;
}

void connectClient(char* http_request){

  if (client.connect()) {
    Serial.println("connected");
    Serial.println(http_request);
    client.print(http_request);
    client.println();
  } else {
    Serial.println("connection failed");
  }
  
  Serial.print("Waiting for the response...");
  while(!client.available()){
    Serial.print('.');
  }
  Serial.println();
}
