#include <ESP8266WiFi.h>        // https://github.com/esp8266/Arduino
#include <ESP8266HTTPClient.h>  // https://github.com/esp8266/Arduino
#include <OneWire.h>
#include <DallasTemperature.h>

// Pin Definitions
int ONE_WIRE_TEMP_PIN = 13;
int FLOW_SENSOR_1_PIN = 2; // depends on pin 2 for interrupt 0

// Constants
const int SERIAL_BAUD_RATE = 9600;
const int LOOP_DELAY_IN_MS = 1000;
const int FLOW_SENSOR_1_INTERRUPT = 0;
const char* WIFI_SSID = "MondoKegBot";
const char* WIFI_PASSWORD = "mondorobot";
const int MAX_RETRY_SECONDS = 25;
const char HTTP_POST_URL[] = "url to post data";

// Library instantiations
OneWire oneWire(ONE_WIRE_TEMP_PIN);
DallasTemperature tempSensors(&oneWire);
HTTPClient http;

// Global variables
float pulseCount;           // Main pulses counter
float pulseCountCopy;       // Auxiliary counter
float pulseCountPrev;       // Auxiliary counter to track pulses activity between loops

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.print(WIFI_SSID);

  pinMode(FLOW_SENSOR_1_PIN, INPUT);
  tempSensors.begin();

  initWifi();

  // Interrupt is attached to addPulses function (Flow sensor 1)
  attachInterrupt(FLOW_SENSOR_1_INTERRUPT, addPulses, RISING);

  // Enable interrupts for a RISING signal. (Flow sensors)
  sei();
}

void loop() {
  // Disable interrupts to check the counter
  cli();
  // Copy the ISR variable (main counter). Don't corrupt the counting process
  pulseCountCopy = pulseCount;
  // Enable interrupts
  sei();

  // If pulses are non-zero and don't change during a loop,
  // send the data to the Serial port
  if ((pulseCountCopy != 0) && (pulseCountPrev == pulseCountCopy)) {
    getFlowSensorReadings();
  } else {
    Serial.println("No reading");
  }
  // Disable interrupts to copy the pulses count
  cli();
  pulseCountPrev = pulseCountCopy;
  // Re-enable interrupts
  sei();

  // TODO: Move this out of the loop() function and into a timer instantiated in the setup() function
  getTemps();

  delay(LOOP_DELAY_IN_MS);
}

/**
 *  Interrupt Service Routine for interrupt 0 (ISR0)
 *  ISR0 services an interrupt condition on Pin 2 - whenever voltage on that pin rises.
 */
void addPulses () {
  pulseCount += 1; // Every RISING pulse causes pulsesCounter to increase by one.
}

void getTemps() {
  tempSensors.requestTemperatures();

  // TODO: Loop here
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(tempSensors.getTempFByIndex(0));
  Serial.print("Temperature for the device 2 (index 1) is: ");
  Serial.println(tempSensors.getTempFByIndex(1));
  Serial.print("Temperature for the device 3 (index 2) is: ");
  Serial.println(tempSensors.getTempFByIndex(2));
}

void getFlowSensorReadings() {
  Serial.print("PULSES: ");
  Serial.println (pulseCountCopy, DEC);
  cli();
  pulseCount = 0;
  sei();
  pulseCountPrev = 0;
  pulseCountCopy = 0;
}

void initWifi() {
  delay(5000);
  int secondsElapsed = 0;

  WiFi.mode(WIFI_STA);

  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    if (secondsElapsed > MAX_RETRY_SECONDS) {
      Serial.println("Unable to connect.");
      return;
    }

    delay(1000);
    Serial.print(".");
    secondsElapsed += 1;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\r\nWiFi connected");
  }
}
