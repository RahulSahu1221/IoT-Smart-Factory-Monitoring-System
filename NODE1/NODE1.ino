//NODE1.ino
//include required libraries
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <DHT.h>

#include "config.h"
#include "SensorManager.h"
#include "actuator.h"
#include "network.h"
#include "telemetry.h"
#include "rpc.h"

static char sharedBuf[200];

//create object of type ethernt pubsubclient
static EthernetClient ethClient;
static PubSubClient mqttClient(ethClient);

unsigned long lastTelemetry =  0;
void setup() 
{
  Serial.begin(9600);
  Serial.print("Node1 is booting...");
  // put your setup code here, to run once:
  //initialise sensor
  sensor_begin();

  //initialise actuators
  actuators_begin();

  telemetry_init(sharedBuf, sizeof(sharedBuf));
  rpc_init(&mqttClient, sharedBuf, sizeof(sharedBuf));   //initialising rpc request

  //upon receiving the data which function needs to be called 
  mqttClient.setCallback(rpc_mqttCallback);
  //connect board to intenet and mqtt
  network_begin(&mqttClient);
  

  digitalWrite(PIN_LED_RED, LOW); 
}

void loop() 
{
  // Keep checking network connection stability
  network_maintain();
  
  static SensorData data;
  unsigned long now = millis();

  // FIX: Read sensors non-blockingly every 2 seconds instead of clogging the stack
  static unsigned long lastSensorRead = 0;
  if (now - lastSensorRead >= 2000UL)
  {
    lastSensorRead = now;
    sensors_read(&data); // Reads your DHT22, LM35, and Vibration
    actuators_setRelay(data.lm35Temp >= 125.0f ? 1 : 0);
  }

  // Publish to the cloud every 5 seconds
  if(network_isConnected())
  {
    // FIX: Added () to execute actuators_getRelayState as a function call!
    if (now - lastTelemetry >= TELEMETRY_INTERVAL)   
    {
      lastTelemetry = now;
      telemetry_publishTelemetry(&data, actuators_getRelayState());   
    }
  }
  actuators_updateStatusLEDs(network_isConnected(), data.sensorError);
}