//libraries for DHT sensor and BMP sensor
#include "DHT.h"
#include <Adafruit_Sensor.h> 
#include "Adafruit_BMP3XX.h"

//signal pin is A0
#define DHTPIN A0
//The DHT sensor type is DHT11
#define DHTTYPE DHT11
#define SEALEVELPRESSURE_HPA (1013.25)

//DHT and BMP sensor variable
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP3XX bmp;

//main function
void setup() {
  Serial.begin(9600);
  //checks if the sensor is found
  if(!bmp.begin_I2C()){
    Serial.println("Could not find a valid BMP388 sensor, check wiring!");
  }

  //changes some bmp sensor settings
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
  //starts dht sensor
  dht.begin();
  
}

//this function will loop continuously after the main function
void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature(true);
  //checking if sensor returns nan
  if(isnan(h) || isnan(t)){
    Serial.println(F("Failed to read from DHT sensor!"));
  } else {
     //prints out humidity and temperature
     Serial.print(F("Humidity: "));
     Serial.print(h);
     Serial.print(F("%  Temperature: "));
     Serial.print(t);
     Serial.print(F("°F "));
     Serial.println();
  }
  
  if(!bmp.performReading()){
    Serial.println("Failed to perform reading.");
  } else {
    //prints out pressure and altitude
    Serial.print("Pressure: "); 
    Serial.print(bmp.pressure / 100.0); 
    Serial.print(" hPa Altitude: ");
    Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA)); 
    Serial.println("m");
  }
}
