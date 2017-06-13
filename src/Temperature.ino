#include <OneWire.h>            // https://github.com/PaulStoffregen/OneWire
#include <DallasTemperature.h>  // https://github.com/milesburton/Arduino-Temperature-Control-Library

OneWire oneWire(2);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  delay(10);

  sensors.begin();
}

void loop() {
  delay(1000);

  sensors.requestTemperatures();
   Serial.print("Temperature for the device 1 (index 0) is: ");
   Serial.println(sensors.getTempFByIndex(0));
}
