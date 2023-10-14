volatile int flow_frequency; 
unsigned int l_hour; 
unsigned long currentTime;
unsigned long cloopTime;
#include <SPI.h>
#include <LoRa_STM32.h>
 
#define SS PA4
#define RST PB0
#define DI0 PA1
 
#define TX_P 17
#define BAND 433E6
#define ENCRYPT 0x78
void flow () 
{
   flow_frequency++;
}
void setup()
{
   pinMode(PA0, INPUT);
   digitalWrite(PA0, HIGH); 
   Serial.begin(115200);
     while (!Serial);
 
  Serial.println("LoRa Sender");
 
  LoRa.setTxPower(TX_P);
  LoRa.setSyncWord(ENCRYPT);
  
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(BAND)) 
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
   attachInterrupt(PA0, flow, CHANGE); 
   interrupts();
   currentTime = millis();
   cloopTime = currentTime;
}
void loop ()
{
   currentTime = millis();
   
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; 
      l_hour = (flow_frequency * 60 / 7.5); 
        LoRa.beginPacket();
        LoRa.print(flow_frequency);
        LoRa.endPacket();
      flow_frequency = 0; 
      Serial.print(l_hour, DEC); 
      Serial.println(" L/hour");
     
   }
}
