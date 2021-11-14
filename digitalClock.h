/*******************************************************/
/*              SETUP DIGITAL CLOCK                    */
/*******************************************************/
#define DEFAULT_CLOCK_TEXTCOLOR  0x0829 //0x18E3         //Clock Font Color
#define DEFAULT_CLOCK_BACKGROND  0xDC5A //0xF7F5 //0xFF51         //Clock BG   Color
#define DEFAULT_CLOCK_TEXTSIZE   2
#define DEFAULT_NTP_SERVER       "1.th.pool.ntp.org"
#define DEFAULT_TIME_ZONE        25200  //+7.00
/*******************************************************/
TFT_eSPI tft = TFT_eSPI();

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, DEFAULT_NTP_SERVER, DEFAULT_TIME_ZONE);

/* Start Clock Variable*/
uint32_t targetTime = 0;                   
byte omm = 99, oss = 99;
byte xcolon = 0, xsecs = 0;
unsigned int colour = 0;
/* End Clock Variable*/

void digitalClock(int xpos, int ypos){                                                     // Display digital clock Function
  timeClient.update();
  tft.setTextColor(DEFAULT_CLOCK_TEXTCOLOR, DEFAULT_CLOCK_BACKGROND);
  tft.setTextSize(DEFAULT_CLOCK_TEXTSIZE);
  unsigned int hh = timeClient.getHours();
  unsigned int mm = timeClient.getMinutes();
  unsigned int ss = timeClient.getSeconds();                                                               // Set next update for 1 second later

  // Draw hours and minutes
  if(hh < 10) xpos += tft.drawChar('0', xpos, ypos);                                  // Add hours leading zero for 24 hr clock
  xpos += tft.drawNumber(hh, xpos, ypos);                                              // Draw hours
  xcolon = xpos;                                                                       // Save colon coord for later to flash on/off later
  xpos += tft.drawChar(':', xpos, ypos);
  if(mm < 10) xpos += tft.drawChar('0', xpos, ypos);                                  // Add minutes leading zero
  xpos += tft.drawNumber(mm, xpos, ypos);                                              // Draw minutes
  xsecs = xpos;                                                                        // Sae seconds 'x' position for later display updates
  xpos = xsecs;

  // Seconds colon
  tft.drawChar(':', xcolon, ypos);                                                     // Hour:minute colon
  xpos += tft.drawChar(':', xsecs, ypos); 
  
  //Draw seconds
  tft.setTextColor(DEFAULT_CLOCK_TEXTCOLOR, DEFAULT_CLOCK_BACKGROND);
  if (ss < 10) xpos += tft.drawChar('0', xpos, ypos);                                  // Add leading zero
  tft.drawNumber(ss, xpos, ypos);                                                     // Draw seconds
}
