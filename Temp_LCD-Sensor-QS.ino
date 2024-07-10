/*This program allows you to display temperature and humidity using a DHT11 sensor and an LCD screen. The display progrmaming is a little janky. I may need to look at 
the intervals at which the temp and humidity is measured.*/

#include <LiquidCrystal.h> 
#include <Arduino.h>
#include <DHT11.h>
const int temp_sensor_pin = 13;

DHT11 temp_sensor(temp_sensor_pin); //Creates an object for the DHT11

int count = 0;
int Contrast=100;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  //list all pins connected to LCD except for v0 on LCD

 void setup()
 {
    Serial.begin(9600);
    temp_sensor.setDelay(2000); //Prob set to every 30 minutes for plant care.
    analogWrite(6,Contrast); //V0 pin goes here.
    lcd.begin(16, 2);
  } 

     void loop(){
      read_humidity();
      read_temp();
    //count_up();
 }

void read_humidity(){
  float humidity = temp_sensor.readHumidity();
  if(humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT ){    //This checks for a checksum error (error during transmission from sensor to arduino) and a timeout error (hardware defect). If these are not present it reads temp, if the are it will give an error string.
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");
    lcd.setCursor(0, 1);
    lcd.print(humidity); //can test this by printing to serial monitor instead of LCD.
  } else{
    lcd.setCursor(0, 0);
    lcd.print(DHT11::getErrorString(humidity));
  }
}

void read_temp(){
  float temp = temp_sensor.readTemperature();
  if(temp != DHT11::ERROR_CHECKSUM && temp != DHT11::ERROR_TIMEOUT){
    float converted_temp = c_to_f(temp);
    lcd.setCursor(10, 0);
    lcd.print("Temp: ");
    lcd.setCursor(10, 1);
    lcd.print(converted_temp); //can test this by printing to serial monitor instead of LCD.
  } else{
    lcd.setCursor(0, 0);
    lcd.print(DHT11::getErrorString(temp));
  }
}

float c_to_f(float temp_in_c){
  return (temp_in_c) * (9./5.) + 32;  //REMEMBER TO PUT A DECIMAL POINT SO THAT THE INTS BECOME FLOATS SO THE MATH CHECKS OUT
}
