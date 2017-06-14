#include <OneWire.h>
#include <DallasTemperature.h>

// Pin Definitions
int ONE_WIRE_TEMP_PIN = 7;
int FLOW_SENSOR_1_PIN = 2; // depends on pin 2 for interrupt 0

// Constants
int SERIAL_BAUD_RATE = 9600;
int LOOP_DELAY_IN_MS = 1000;
int FLOW_SENSOR_1_INTERRUPT = 0;

// Library instantiations
OneWire oneWire(ONE_WIRE_TEMP_PIN);
DallasTemperature tempSensors(&oneWire);

// Global variables
float pulseCount;           // Main pulses counter
float pulseCountCopy;       // Auxiliary counter
float pulseCountPrev;       // Auxiliary counter to track pulses activity between loops

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);

  pinMode(FLOW_SENSOR_1_PIN, INPUT);
  tempSensors.begin();

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
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(tempSensors.getTempFByIndex(0));
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
