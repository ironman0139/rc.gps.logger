#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <TFT.h>  // Arduino LCD library
/*
   This sample code demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 3, TXPin = 4;
static const uint32_t GPSBaud = 9600;

#define sd_cs  6
#define lcd_cs 10
#define dc     9
#define rst    8

int datafile = 0;
int data = 0;
int nmea = 0;
int sat = 0;

int valday = 0;
int valmonth = 0;
int valyear = 0;
int valhour = 0;
int valminute = 0;
int valsecond = 0;
int valspeed = 0;
int valalt = 0;
float vallat = 0;
float vallong = 0;
String stringOne;
String stringTwo;
String stringThree;

TFT TFTscreen = TFT(lcd_cs, dc, rst);

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);

  // see if the card is present and can be initialized:
  if (!SD.begin(sd_cs)) {
   
    // don't do anything more:
    while (1);
  }
 
  TFTscreen.begin();
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextColor(ST7735_WHITE,ST7735_BLACK);
  TFTscreen.setTextSize(1);
  TFTscreen.setCursor(5, 110);
  TFTscreen.println();
  TFTscreen.println(F("card initialized."));

}

void loop()
{

  //sat = gps.satellites.value();
  sat = 1;

  
if (sat == 0) {
 // keine Daten vorhanden
      TFTscreen.setCursor(0, 90);
      TFTscreen.setTextColor(ST7735_WHITE,ST7735_BLACK);
      TFTscreen.print("Keine Sateliten vorhanden");
      TFTscreen.setTextColor(ST7735_CYAN,ST7735_BLACK);

}

else { 



  

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

 /* printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
//  printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  printInt(gps.location.age(), gps.location.isValid(), 5);
  printDateTime(gps.date, gps.time);
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6);*/


      TFTscreen.setCursor(5, 7);
      TFTscreen.setTextColor(ST7735_WHITE,ST7735_BLACK);
      TFTscreen.print("Datum: ");
      TFTscreen.setTextColor(ST7735_CYAN,ST7735_BLACK);
      TFTscreen.print(gps.date.day());
      TFTscreen.print(".");
      TFTscreen.print(gps.date.month());
      TFTscreen.print(".");
      TFTscreen.print(gps.date.year());

      TFTscreen.setCursor(5, 20);
      TFTscreen.setTextColor(ST7735_WHITE,ST7735_BLACK);
      TFTscreen.print("Lat: ");
      TFTscreen.setTextColor(ST7735_CYAN,ST7735_BLACK);
      TFTscreen.print(gps.location.lat(),6);
      Serial.print(gps.location.lat(),6);
      
      TFTscreen.setCursor(5, 30);
      TFTscreen.setTextColor(ST7735_WHITE,ST7735_BLACK);
      TFTscreen.print("Long: ");
      TFTscreen.setTextColor(ST7735_CYAN,ST7735_BLACK);
      TFTscreen.print(gps.location.lng(),6);

      TFTscreen.setCursor(5, 40);
      TFTscreen.setTextColor(ST7735_WHITE,ST7735_BLACK);
      TFTscreen.print("Sat: ");
      TFTscreen.setTextColor(ST7735_CYAN,ST7735_BLACK);
      TFTscreen.print(gps.satellites.value());

      TFTscreen.setCursor(5, 50);
      TFTscreen.setTextColor(ST7735_WHITE,ST7735_BLACK);
      TFTscreen.print("Alt: ");
      TFTscreen.setTextColor(ST7735_CYAN,ST7735_BLACK);
      TFTscreen.print(gps.altitude.meters());

      TFTscreen.setCursor(5, 60);
      TFTscreen.setTextColor(ST7735_WHITE,ST7735_BLACK);
      TFTscreen.print("Speed: ");
      TFTscreen.setTextColor(ST7735_CYAN,ST7735_BLACK);
      TFTscreen.print(gps.speed.kmph());

      
valday = gps.date.day();
valmonth = gps.date.month();
valyear = gps.date.year();
valhour = gps.time.hour();
valminute = (gps.time.minute(),2);
valsecond = (gps.time.second(),2);
valspeed = gps.speed.kmph();
valalt = (gps.altitude.meters());
vallat = (gps.location.lat());
String lat1 = String(vallat,6);
vallong = (gps.location.lng());
String long1 = String(vallong,6);
stringOne = ".";
stringTwo = "; ";
stringThree = ":";
String datafile = valday + stringOne + valmonth + stringOne + valyear + stringTwo + valhour + stringThree + valminute + stringThree + valsecond + stringTwo + valspeed + stringTwo + valalt + stringTwo + lat1 + stringTwo + long1 + stringTwo;

      TFTscreen.setCursor(5, 70);
      TFTscreen.setTextColor(ST7735_WHITE,ST7735_BLACK);
      TFTscreen.print("UTC: ");
      TFTscreen.setTextColor(ST7735_CYAN,ST7735_BLACK);
      TFTscreen.print(valhour);
      TFTscreen.print(":");
      TFTscreen.print(gps.time.minute());
      TFTscreen.print(":");
      TFTscreen.print(gps.time.second());
      TFTscreen.print("");
      TFTscreen.setTextColor(ST7735_WHITE,ST7735_BLACK);
      
  //datafile=(gps.date.day());
  if (dataFile) {
    dataFile.println(datafile);
    dataFile.close();
    // print to the serial port too:
    //Serial.println(datafile);
  }


  File Nmea = SD.open("nmea.txt", FILE_WRITE);
  String nmea = lat1 + stringTwo + long1 + stringTwo + valalt;
   if (nmea) {
    Nmea.println(nmea);
    Nmea.close();
    // print to the serial port too:
    //Serial.println(datafile);
  }

  unsigned long distanceKmToLondon =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON) / 1000;
  printInt(distanceKmToLondon, gps.location.isValid(), 9);

  double courseToLondon =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON);

  printFloat(courseToLondon, gps.location.isValid(), 7, 2);

  const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

  printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6);

  printInt(gps.charsProcessed(), true, 6);
  printInt(gps.sentencesWithFix(), true, 10);
  printInt(gps.failedChecksum(), true, 9);
  Serial.println();
  
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}


}


// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}
