#include <TinyGPS++.h>
#include <Wire.h> 

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20,16,2); 
TinyGPSPlus gps;
void getgps(TinyGPSPlus &gps);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
}

void getgps(TinyGPSPlus &gps)
{
  if (gps.location.isValid() and gps.date.isValid() and gps.time.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    //Serial.print("Altitude: ");
    //Serial.println(gps.altitude.meters());
    lcd.setCursor(0,0);
    lcd.print("lat->");
    lcd.print(gps.location.lat(), 6);
    lcd.setCursor(0,1);
    lcd.print("lon->");
    lcd.print(gps.location.lng(), 6);
    delay(2000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Date->");
    lcd.print(gps.date.month());
    lcd.print("/");
    lcd.print(gps.date.day());
    lcd.print("/");
    lcd.print(gps.date.year());
    lcd.setCursor(0,1);
    
    lcd.print("Time->");
    lcd.print(gps.time.hour());
    lcd.print(":");
    lcd.print(gps.time.minute());
    lcd.print(":");
    lcd.print(gps.time.second());
    delay(2000);
    lcd.clear();
    
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  
  
 
}

void loop() {
  // put your main code here, to run repeatedly:
  byte a;
  if (Serial.available() > 0 )
  {
    a = Serial.read();
    if (gps.encode(a))
    {
      getgps(gps);
    }
  }
}
