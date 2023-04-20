/*

------ COMPONENTS -----
1.MQ135 sensor
2.DHT11 sensor
3.LCD 
4.Arduino uno

*/


#include <Wire.h>              
#include <LiquidCrystal_I2C.h> // library for lcd
#include <DHT.h> // library for temp&hum sensor
#define DHTPIN 2 // temp sensor pin
#define DHTTYPE DHT11  // dht type -> DHT11
DHT dht(DHTPIN, DHTTYPE); // define pin value and dht type
    

int pin = A0;  // air sensor pin 

LiquidCrystal_I2C lcd(0x27, 16, 2);  // lcd dispay grid value


void setup(){

  pinMode(pin, INPUT);  // air sensor pinMode
 
  lcd.init();
  lcd.begin(16,2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(4,0);
  dht.begin();

  Serial.begin(9600);  // 
}

void loop(){

  int air_quality = analogRead(pin); // read pin value
  float h = dht.readHumidity();  // read humidity
  float t = dht.readTemperature(); // read temprature

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }


  if (air_quality<=1000){

    // Display Air quality
    lcd.setCursor(0,0);
    lcd.print("air:");
    lcd.print(air_quality);
    lcd.setCursor(7,0);
    lcd.print("Fresh Air");

  }else if( air_quality>=1000 && air_quality<=2000 ){

    // Display Air quality
    lcd.setCursor(0,0);
    lcd.print("air:");
    lcd.print(air_quality);
    lcd.print("Poor Air, Open Windows");

  }else if (air_quality>=2000 ){

    // Display Air quality
    lcd.setCursor(0,0);
    lcd.print("air:");
    lcd.print(air_quality);
    lcd.print("Danger! Move to Fresh Air");
  }


  // Dispaly Temperature
  lcd.setCursor(0,1);
  lcd.print("tmp:");
  lcd.print(t);
  lcd.print("C");


  // Display Humidity
  lcd.setCursor(8,1);
  lcd.print("hum:");
  lcd.print(h);
  lcd.print("%");

  delay(1000);

}
  

