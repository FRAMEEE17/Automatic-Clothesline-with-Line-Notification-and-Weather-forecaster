
//Reset_btn
#define RECONFIG_BUTTON 9
//Dht
#define DHT_PIN       12           

//Motor
#define MOTOR_IN1     5        
#define MOTOR_IN2     4                

//Limit SW

#define LIMITSW      10
//#define LIMITSW2      10
//Rain drop
#define RAINDROP_PIN  16

#define BLYNK_PRINT Serial
#define LINE_TOKEN  "mkGylK8JqyDUGHdPT5FW83Ip7pdy4elnRR2SVkNcRw0"
/*include libraly*/
#include <ArduinoJson.h>

#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <DNSServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <NTPClient.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <TridentTD_LineNotify.h>
#include <WiFiClient.h>
#include <WiFiManager.h> 
#include <WiFiUdp.h>
#include <ArduinoHttpClient.h>

/*include source file*/
#include "openWeather.h"
#include "digitalClock.h"
#include "open_weather_icons.h"
#include "icons.h"
#include "tft_screen.h"

/*               SETUP CLOTHES LINE                    */
/*******************************************************/
#define CHECK_POSIBILITY_DELAY 5000
#define RAINING_NOTIFY_DELAY   600000 //10*60*1000
/*******************************************************/

unsigned long last_notify           = 0; 
unsigned long last_check_posibility = 0;
int motorStatus = 0;
int open_or_close = 0; //clothesline is opened or closed
//int RAINDROP_VAL = 0;
DHT dht(DHT_PIN,DHT22);

char blynk_token[]= "UCLWTtcvuvnBcQ6WGchnWNTCWv0mJPmZ";
//char line_tokon[39];
  
//WiFiManagerParameter custom_blynk_token("Blynk", "blynk token", blynk_token, 33);


/*Define Object*/
WiFiManager wifiManager;                                  // WiFi Manager

void setup (void) {
  Serial.begin(115200);
  screenSetup();
 // resetWiFiManagerConfig();
  tft.fillScreen(DEFAULT_BACKGROND);
  tft.drawString("Connect to WiFI", 75, 150,2);

  //wifiManager.addParameter(&custom_blynk_token);
  
  wifiManager.autoConnect("AutoConnectAP");
  Blynk.config(blynk_token);
  LINE.setToken(LINE_TOKEN);
  timeClient.begin();
  delay(2000);
 
  //LINE.notify("เริ่มต้นใช้งาน ราวตากผ้าอัจฉริยะ");
  
  dht.begin();
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
  pinMode(LIMITSW,INPUT);
  //pinMode(LIMITSW2,INPUT);
  pinMode(RAINDROP_PIN,INPUT);
  tft.fillScreen(DEFAULT_BACKGROND);
  tft.drawString("Setting Up Device", 70, 150,2);
  sendHttpRequest();
  delay(2000);
  drawOpenweatherData();
  Serial.println("check 1");
}

void loop() {
  Blynk.run();
  //sendOpenWeatherResquest();
  //homeScreen();
  calculateRainPosibility();
  checkLimitSW();
 // checkPossibility(int possibility);
  checkRAINDROP();
}

void resetWiFiManagerConfig(){                                                                  // Reset WiFi Setting
  pinMode(RECONFIG_BUTTON, INPUT);
  Serial.println(digitalRead(RECONFIG_BUTTON));
  if(digitalRead(RECONFIG_BUTTON) == 1 ){
      Serial.println("Reset Config");
      wifiManager.resetSettings();
  }
}

void calculateRainPosibility(){
  if((millis() - last_check_posibility) > CHECK_POSIBILITY_DELAY) {
    
    float Humidity = dht.readHumidity();
    float Temperature = dht.readTemperature();
    
    int   possibility;
    
    Serial.print("Humidity    =  ");   Serial.print(Humidity);    Serial.println("%  ");
    Serial.print("Temperature =  ");   Serial.print(Temperature); Serial.println("C  \n");

    Blynk.virtualWrite(V0, Temperature);
    Blynk.virtualWrite(V1, Humidity);
  unsigned int hh = timeClient.getHours();
    
    if(hh >= 1 && hh <= 3 )
      if(Humidity >= 90.0) possibility = 3; 
      else if(Humidity >= 85.0 && Humidity < 90.0)
        if(Temperature < 29) possibility = 2;
        else possibility = 0;
      else if(Humidity >=80.0 && Humidity < 85.0)
        if(Temperature < 29.25) possibility = 2;
        else possibility = 0;
      else if(Humidity <80)
        if(Temperature < 28.65) possibility = 1;
        else possibility = 0;
   if(hh >= 4 && hh <= 6 )
      if(Humidity >= 90.0) possibility = 3; 
      else if(Humidity >= 85.0 && Humidity < 90.0)
        if(Temperature < 28) possibility = 2;
        else possibility = 0;
      else if(Humidity >=80.0 && Humidity < 85.0)
        if(Temperature < 28.50) possibility = 2;
        else possibility = 0;
      else if(Humidity <80) possibility = 0;
   if(hh >= 7 && hh <= 9)
      if(Humidity >= 90.0) possibility = 3; 
      else if(Humidity >= 85.0 && Humidity < 90.0)
        if(Temperature < 27.85) possibility = 2;
        else possibility = 0;
      else if(Humidity >=80.0 && Humidity < 85.0)
        if(Temperature < 28.00) possibility = 2;
        else possibility = 0;
      else if(Humidity <80) possibility = 0;
   if(hh >= 10 && hh <= 12)
      if(Humidity >= 90.0) possibility = 3; 
      else if(Humidity >= 85.0 && Humidity < 90.0)
        if(Temperature < 28.00) possibility = 2;
        else possibility = 0;
      else if(Humidity >=80.0 && Humidity < 85.0)
        if(Temperature < 27.00) possibility = 2;
        else possibility = 0;
      else if(Humidity <80) 
        if(Temperature < 29.0) possibility = 1;
        else possibility = 0;
   if(hh >= 13 && hh <= 15)
      if(Humidity >= 90.0) possibility = 3; 
      else if(Humidity >= 85.0 && Humidity < 90.0)
        if(Temperature < 28.00) possibility = 2;
        else possibility = 0;
      else if(Humidity >=80.0 && Humidity < 85.0)
        if(Temperature < 30.65) possibility = 2;
        else possibility = 0;
      else if(Humidity <80) 
        if(Temperature < 32.0) possibility = 1;
        else possibility = 0;
   if(hh >= 16 && hh <= 18)
      if(Humidity >= 90.0) possibility = 3; 
      else if(Humidity >= 85.0 && Humidity < 90.0)
        if(Temperature < 29.00) possibility = 2;
        else possibility = 0;
      else if(Humidity >=80.0 && Humidity < 85.0)
        if(Temperature < 29.00) possibility = 2;
        else possibility = 0;
      else if(Humidity <80) 
        if(Temperature < 31.0) possibility = 1;
        else possibility = 0;
   if(hh >= 19 && hh <= 21)
      if(Humidity >= 90.0) possibility = 3; 
      else if(Humidity >= 85.0 && Humidity < 90.0)
        if(Temperature < 28.00) possibility = 2;
        else possibility = 0;
      else if(Humidity >=80.0 && Humidity < 85.0)
        if(Temperature < 28.50) possibility = 2;
        else possibility = 0;
      else if(Humidity <80) 
        if(Temperature < 31.0) possibility = 1;
        else possibility = 0;
   if(hh >= 22 && hh <= 23 || hh == 0)
      if(Humidity >= 90.0) possibility = 3; 
      else if(Humidity >= 85.0 && Humidity < 90.0)
        if(Temperature < 27.50) possibility = 2;
        else possibility = 0;
      else if(Humidity >=80.0 && Humidity < 85.0)
        if(Temperature < 28.50) possibility = 2;
        else possibility = 0;
      else if(Humidity <80) 
        if(Temperature < 29.0) possibility = 1;
        else possibility = 0;
    
  switch (possibility){
     
      case 0:  Serial.print("very low chance  \n"); break;
      case 1:  Serial.print("moderate chance \n");  break;
      case 2:  Serial.print("high chance \n");      break;
      case 3:  Serial.print("very high chance \n");
    }
    checkPossibility(possibility);
    last_check_posibility = millis();
    return;
  }
}
/*void checkPossibility(int possibility){   //check possibility 4 5 while close clothesline,if not true openclothesline
  if(possibility == 2||possibility == 3){
    if(digitalRead(RAINDROP_PIN) == 0) {
      //Serial.println("Rain Detected"); //true
      if(open_or_close == 1){//status:close clothesline
        closeClothesline();
      }
    }
    else { 
     //Serial.println("Rain Not Detected"); 
     if((millis() - last_notify) > RAINING_NOTIFY_DELAY){//send every 10 minutes
        LINE.notify("ฝนจะตกแล้ว มาเก็บผ้าด่วนจ้าาาา "); 
        last_notify = millis();
      }
    }
  } 
  else {
    if(open_or_close == 0){//status:open clothesline
      openClothesline();
    }
  }
} */ 
void checkPossibility(int possibility){   //check possibility 4 5 while close clothesline,if not true openclothesline
  if(possibility == 2||possibility == 3){
    if(digitalRead(RAINDROP_PIN) == 1) {
      //Serial.println("Rain Detected"); //true
      if((millis() - last_notify) > RAINING_NOTIFY_DELAY){//send every 10 minutes
        LINE.notify("ฝนจะตกแล้ว มาเก็บผ้าด่วนจ้าาาา "); 
        last_notify = millis();
      }
    }
  }
}
void openClothesline(){
  if(motorStatus == 0){
      Serial.println("openClothesline"); 
      digitalWrite(MOTOR_IN1, HIGH);
      digitalWrite(MOTOR_IN2, LOW);
      motorStatus = 1;
  }
}
void closeClothesline(){
      Serial.println("closeClothesline");
      digitalWrite(MOTOR_IN1, LOW);
      digitalWrite(MOTOR_IN2, HIGH);
      motorStatus = 1;   
}
void checkRAINDROP(){
    if(digitalRead(RAINDROP_PIN) == 0&& digitalRead(LIMITSW) == 0){//
      closeClothesline();
      open_or_close =!open_or_close;
    }
    /*else {
      if(digitalRead(RAINDROP_PIN) == 1&& digitalRead(LIMITSW2) == 0){
      openClothesline();
      open_or_close =!open_or_close;
      }
    }
    /*if(digitalRead(RAINDROP_PIN) == 0&& digitalRead(LIMITSW) == 0){
      closeClothesline();
    }
    /*else if(digitalRead(RAINDROP_PIN) == 0&& digitalRead(LIMITSW) == 1){//
      stopClothesline();
      open_or_close =!open_or_close;
    }
    else if(digitalRead(RAINDROP_PIN) == 1&& digitalRead(LIMITSW) == 0){
      openClothesline();
    }
    else if(digitalRead(RAINDROP_PIN) == 1&& digitalRead(LIMITSW) == 1){//limitsw2
      stopClothesline();
      open_or_close =!open_or_close;
    }
    
    /*else if(digitalRead(RAINDROP_PIN) == 1&& digitalRead(LIMITSW) == 1){
      openClothesline();
      open_or_close =!open_or_close;
    }*/   
}
void stopClothesline(){
   Serial.println("stopClothesline"); 
   digitalWrite(MOTOR_IN1, LOW);
   digitalWrite(MOTOR_IN2, LOW);
   motorStatus = 0;
}
void checkLimitSW(){
    if(digitalRead(LIMITSW) == 1){
      stopClothesline();
      open_or_close =!open_or_close;
    }   
}
