#include "actuator.h"

static uint8_t relay_status; 
static uint8_t blinkState = 0;
static unsigned long lastBlinkTime = 0;

void actuators_begin(void)
{
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_LED_YELLOW, OUTPUT);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_RELAY, OUTPUT);
  
  //in the begining till network connection, LED be ON
  digitalWrite(PIN_LED_GREEN, LOW);     //If on, everything is normal
  digitalWrite(PIN_LED_YELLOW, LOW);  //if on; warning, blinking; critical
  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_RELAY, LOW);   //ventilation, if more humidity

}

void actuators_setRelay(uint8_t on)
{
  relay_status = on;
  digitalWrite(PIN_RELAY, on ? HIGH : LOW);
}


uint8_t actuators_getRelayState(void)
{
  return relay_status;
}

void actuators_updateStatusLEDs(uint8_t mqttConnected, uint8_t sensorError)
{
  //if board is not connected to things board --> turn on RED led
  if(!mqttConnected)
  {
    digitalWrite(PIN_LED_RED, HIGH);  
    digitalWrite(PIN_LED_GREEN, LOW);  
    digitalWrite(PIN_LED_YELLOW, LOW);  
    return;
  }
    //if mqtt is up, turn off RED led
    digitalWrite(PIN_LED_RED, LOW);  
 
  //if sensor error then blink YELLOW led
    if(sensorError)
    {
      //blink Yellow LED
      digitalWrite(PIN_LED_GREEN, HIGH); 
      unsigned long now = millis(); 
      if(now - lastBlinkTime > 500) //half a sec delay to blink the led
      {
        lastBlinkTime = now;
        blinkState = !blinkState;
        digitalWrite(PIN_LED_YELLOW, blinkState ? HIGH : LOW);
      }
    }
    else 
      {
        //if all good; no error
        digitalWrite(PIN_LED_YELLOW, LOW);  
        digitalWrite(PIN_LED_GREEN, HIGH); 
      }

   //if everything is normal turn on GREEN led
  
  
}
