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


static SensorManager  sensors;

void setup() 
{
  Serial.begin(9600);
  Serial.print("Node2 is booting...");
  // put your setup code here, to run once:
  //initialise sensor
  sensor_begin();
  sensor_init(&sensors);

  //initialise actuators
  actuators_begin();

  telemetry_init(sharedBuf, sizeof(sharedBuf));
  rpc_init(&mqttClient, sharedBuf, sizeof(sharedBuf));   //initialising rpc request
  
  mqttClient.setCallback(rpc_mqttCallback);

  //connect board to intenet and mqtt
  network_begin(&mqttClient);

}

void loop() 
{
  // Keep checking network connection status
  network_maintain(); 
  
  static SensorData data;
  unsigned long now = millis(); 

  // FIX: Only read sensors once every 2 seconds instead of every single loop iteration
  static unsigned long lastSensorRead = 0;
  if (now - lastSensorRead >= 2000UL)
  {
    lastSensorRead = now;
    sensor_read(&data, &sensors); 

    // Automatic threshold control for the ventilation relay
    if (data.humidity >= HUMIDITY_CRIT) 
    {
      if (!actuators_getRelayState()) 
      {
        actuators_setRelay(1); 
      }
    }
    else 
    {
      if (actuators_getRelayState()) 
      {
        actuators_setRelay(0); 
      }
    }
  }

  // Publish telemetry to the cloud every 5 seconds
  if(network_isConnected()) 
  {
    if (now - lastTelemetry >= TELEMETRY_INTERVAL) 
    {
      lastTelemetry = now; 
      telemetry_publishTelemetry(&data, actuators_getRelayState()); 
    }
  }
  actuators_updateStatusLEDs(network_isConnected(), data.sensorError); 
}
