/*******************************************************/
/*               SETUP DISPLAY SCREEN                  */
/*******************************************************/
#define DEFAULT_TEXTCOLOR  0x0829 //0x18E3
#define DEFAULT_BACKGROND  0xDC5A //0xF7F5 //0xFF51
#define DEFAULT_REFRESH    60000
/*******************************************************/

/*Pre-define Function*/
void testWeatherIcon();
void drawColorFullIcon(const uint16_t *icon , int x, int y, int w, int h);
void switchWeatherIcon(String iconName);
void drawOpenweatherData();
void testString();

int lastdraw = 0;
unsigned long last_refresh = 0;
void screenSetup(){
  tft.init();
  tft.setRotation(2);
  tft.fillScreen(DEFAULT_BACKGROND);
  tft.setTextColor(DEFAULT_TEXTCOLOR, DEFAULT_BACKGROND);
}

void homeScreen(){
  digitalClock(74,34); //digitalClock(77, 10)
  if(millis() - last_refresh > DEFAULT_REFRESH){
    drawOpenweatherData();
    last_refresh = millis();
  }
}

void testWeatherIcon(){
  if(millis()-lastdraw < 1000)
    drawColorFullIcon(icon_01d, 20, 58, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT);
  else if(millis()-lastdraw < 2000)
    drawColorFullIcon(icon_02d, 20, 58, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT);
  else if(millis()-lastdraw < 3000)
    drawColorFullIcon(icon_03d, 20, 58, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT);
  else if(millis()-lastdraw < 4000)
    drawColorFullIcon(icon_04d, 20, 58, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT);
  else if(millis()-lastdraw < 5000)
    drawColorFullIcon(icon_09d, 20, 58, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT);
  else if(millis()-lastdraw < 6000)
    drawColorFullIcon(icon_10d, 20, 58, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT);
  else if(millis()-lastdraw < 7000)
    drawColorFullIcon(icon_11d, 20, 58, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT);
  else if(millis()-lastdraw < 8000)
    drawColorFullIcon(icon_13d, 20, 58, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT);
  else if(millis()-lastdraw < 9000)
    drawColorFullIcon(icon_50d, 20, 58, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT);
  else
    lastdraw = millis(); 
}

void switchWeatherIcon(String iconName, int x, int y){
  /*if(iconName.equals("01d"))      { drawColorFullIcon(icon_01d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName.equals("02d")) { drawColorFullIcon(icon_02d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName.equals("03d")) { drawColorFullIcon(icon_03d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName.equals("04d")) { drawColorFullIcon(icon_04d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName.equals("09d")) { drawColorFullIcon(icon_09d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName.equals("10d")) { drawColorFullIcon(icon_10d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName.equals("11d")) { drawColorFullIcon(icon_11d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName.equals("13d")) { drawColorFullIcon(icon_13d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName.equals("50d")) { drawColorFullIcon(icon_50d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else                            { Serial.println("Error : Icon not found"); }*/

  if(iconName=="01d")      { drawColorFullIcon(icon_01d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName=="02d") { drawColorFullIcon(icon_02d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName=="03d") { drawColorFullIcon(icon_03d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName=="04d") { drawColorFullIcon(icon_04d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName=="09d") { drawColorFullIcon(icon_09d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName=="10d") { drawColorFullIcon(icon_10d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName=="11d") { drawColorFullIcon(icon_11d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName=="13d") { drawColorFullIcon(icon_13d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else if(iconName=="50d") { drawColorFullIcon(icon_50d, x, y, DEFAULT_ICON_WIDTH, DEFAULT_ICON_HEIGHT); }
  else                            { Serial.println("Error : Icon not found"); }
}

void drawOpenweatherData(){

  tft.fillRect(0,50,240, 270, DEFAULT_BACKGROND);
  tft.setTextColor(DEFAULT_TEXTCOLOR, DEFAULT_BACKGROND);
  tft.setTextSize(2);
  tft.drawString("DATE TIME",68,10);/////////
  
  switchWeatherIcon(opw.icon, 20, 58);
  
  tft.setTextSize(1);
  //tft.drawFloat(opw.pressure, 2, 50, 50);
  tft.drawNumber(opw.humidity, 20, 201);//

  tft.drawFloat(opw.uvindex, 1, 171, 297);//
  tft.drawFloat(opw.pop, 2, 166, 117);//
  tft.drawFloat(opw.temperature, 0, 16, 287);//
  tft.drawFloat(opw.feels, 0, 5, 307);//
  tft.drawFloat(opw.wind, 2, 170, 204);//
  //tft.drawString(opw.description, 14, 117);
  
  tft.setTextColor(DEFAULT_TEXTCOLOR, DEFAULT_BACKGROND);
  tft.setTextSize(1);
  tft.drawString(" RH = " +String(opw.humidity)+" %",20 , 201);//
  tft.drawString(String(opw.uvindex)+" UVI", 171, 297);//
  
 
  
  
  tft.setTextSize(1);
  tft.drawString("POP = " +String(opw.pop), 166, 117);//
  tft.drawString("Temp = " +String(opw.temperature)+" C", 16, 287);//
  tft.drawString("Feel_Like = " +String(opw.feels)+" C", 5, 307);//
  tft.drawString(String(opw.wind) +" m/s", 170, 204);//
  tft.drawString(String(opw.description), 14, 117);
  
  drawColorFullIcon(icon_anemometer,170,139,50,50);
  drawColorFullIcon(icon_temp,20,227,50,50);
  drawColorFullIcon(icon_uvi,170,227,50,50);
  drawColorFullIcon(icon_pop,170,58,50,50);
  
  drawColorFullIcon(icon_humid,20,139,50,50);
     
}
void drawColorFullIcon(const uint16_t *icon , int x, int y, int w, int h){
  int row, col, buffidx=0;
  for (row = y; row < y + w; row++) {
    for (col = x; col < x + h; col++) {
      if(pgm_read_word(icon + buffidx) != 0x0000){
        tft.drawPixel(col, row, pgm_read_word(icon + buffidx));
      }else{
        tft.drawPixel(col, row, DEFAULT_BACKGROND);
      }
      buffidx++;
    }
  }
}
