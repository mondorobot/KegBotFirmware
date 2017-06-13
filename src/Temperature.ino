// #include <OneWire.h>
// #include "DallasTemperature.h"
//
// /* DS18S20 Temperature chip i/o */
//
// // Data wire is plugged into port 10 on the Arduino
// #define ONE_WIRE_BUS 7
// // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
// OneWire oneWire(ONE_WIRE_BUS);
//
// // Pass our oneWire reference to Dallas Temperature.
// DallasTemperature sensors(&oneWire);
//
// void setup(void) {
//   // start serial port
//   Serial.begin(9600);
//   Serial.println("Dallas Temperature IC Control Library Demo");
//
//   // Start up the library
//   sensors.begin();
// }
//
// void loop(void) {
//   // call sensors.requestTemperatures() to issue a global temperature
//   // request to all devices on the bus
//   Serial.println("Requesting temperatures...");
//   sensors.requestTemperatures(); // Send the command to get temperatures
//   Serial.println("DONE");
//   // After we got the temperatures, we can print them here.
//   // We use the function ByIndex, and as an example get the temperature from the first sensor only.
//   Serial.print("Temperature for the device 1 (index 0) is: ");
//   Serial.println(sensors.getTempFByIndex(0));
// }

/*******************************************************************************
  PuffStatus
*******************************************************************************/

#include <OneWire.h>            // https://github.com/PaulStoffregen/OneWire
#include <DallasTemperature.h>  // https://github.com/milesburton/Arduino-Temperature-Control-Library

/*******************************************************************************
  Config. Must provide WIFI_SSID without spaces.
*******************************************************************************/

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
