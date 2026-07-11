//SensorManager.h

#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

#include "config.h"

//all sensor reading packed into one plain struct
typedef struct {
  float temperature;    //DHT22 temperature in degree celcius
  float humidity;       //DHT22 himidity in %
  float lm35Temp;       //LM35 temperature in degree celcius
  uint16_t vibration;    //averaged ADC reading(0-1023)
  uint8_t machineStatus; //1 = button pressed (active low)
  uint8_t sensorError;   //1 = DHT22 read failed 
} SensorData;

void sensor_begin(void);
uint8_t sensors_read(SensorData* out);  //return 0 on DHT error
int sensors_freeMemory(void);           //free SRAM in bytes

#endif  //SENSORS_H