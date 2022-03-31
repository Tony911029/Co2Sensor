#include "CCS811.h"

// CCS811 sensor(&Wire, IIC_ADDRESS=0x5A);
CCS811 sensor;

void setup(void)
{
    Serial.begin(9600);
    pinMode(7, OUTPUT);
    digitalWrite(7, LOW);
    
    /*Wait for the chip to be initialized completely, and then exit*/
    while(sensor.begin() != 0){
        Serial.println("failed to init chip, please check if the chip connection is fine");
        delay(1000);
    }
    /**
     * @brief Set measurement cycle
     * @param cycle:in typedef enum{
     *                  eClosed,      //Idle (Measurements are disabled in this mode)
     *                  eCycle_1s,    //Constant power mode, IAQ measurement every second
     *                  eCycle_10s,   //Pulse heating mode IAQ measurement every 10 seconds
     *                  eCycle_60s,   //Low power pulse heating mode IAQ measurement every 60 seconds
     *                  eCycle_250ms  //Constant power mode, sensor measurement every 250ms
     *                  }eCycle_t;
     */
    sensor.setMeasCycle(sensor.eCycle_250ms);
}
void loop() {
  delay(3000); // time interval
    if(sensor.checkDataReady() == true){
     
        // Serial.print("CO2: ");
        Serial.print(sensor.getCO2PPM());
        Serial.print(",");
        // Serial.print("ppm, TVOC: ");
        Serial.println(sensor.getTVOCPPB());
        // Serial.println("ppb");
        
        if (sensor.getCO2PPM()> 800)
        {
          digitalWrite(7, HIGH);
        }
        else{
          digitalWrite(7, LOW);
        } 
        
    } 
    else {
        Serial.println("Data is not ready!");
    }
    sensor.writeBaseLine(0x847B);
}
