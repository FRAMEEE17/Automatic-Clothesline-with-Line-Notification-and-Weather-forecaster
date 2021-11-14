/*******************************************************/
/*              SETUP OPEN WEATHER API                 */
/*******************************************************/
#define SERVER_NAME     "http://192.241.187.136/data/2.5/onecall"
#define LATITUDE        "13.742580"
#define LONGITUDE       "100.498337"
#define API_TOKEN       "400e5ad429f11e10527ebeb5c9e2a74a"
#define REQUEST_DELAY   300000//5*60*1000

/*******************************************************/
                                                        
void sendOpenWeatherResquest();
void setWeatherData(JsonObject obj);
void sendHttpRequest();

unsigned long last_request = 0;
typedef struct{
  float  temperature;
  float  feels;
  int    pressure;
  int    humidity;
  float  wind;
  float  uvindex;
  String icon;
  String description;
  float  pop;
}open_weather;

open_weather opw;

void sendOpenWeatherResquest(){
  if ((millis() - last_request) > REQUEST_DELAY) {                                                                          //Check time for Send an HTTP POST request
    if(WiFi.status()== WL_CONNECTED){                                                                                       //Check WiFi connection status
      sendHttpRequest();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    last_request = millis();
  }  
}

void setWeatherData(JsonObject obj){
  opw.temperature = obj["temp"];
  opw.feels       = obj["feels_like"];
  opw.pressure    = obj["pressure"];
  opw.humidity    = obj["humidity"];
  opw.wind        = obj["wind_speed"];
  opw.uvindex     = obj["uvi"];
  opw.description = obj["weather"][0]["description"].as<String>();
  opw.icon        = obj["weather"][0]["icon"].as<String>();
  opw.pop         = obj["pop"];
}

void sendHttpRequest(){
  
  String        server_name = SERVER_NAME;
  String        latitude    = LATITUDE;
  String        longitude   = LONGITUDE;
  String        api_key     = API_TOKEN;                                                                                // Open Weather API Key    
  String        serverPath  = server_name + "?lat=" + latitude + "&lon="+longitude + "&units=metric&exclude=daily&appid=" + api_key;
      
  HTTPClient http;
  http.begin(serverPath.c_str());
      
  int httpResponseCode = http.GET();                                                                      // Send HTTP GET request
      
  if(httpResponseCode>0) {                                                                               // Get data from api
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
        
    DynamicJsonDocument doc(8192);
        
    deserializeJson(doc, http.getString());
    setWeatherData(doc["hourly"][1].as<JsonObject>());
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  
  http.end();
}
