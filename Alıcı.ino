#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define  KEY1 0.00
#define  KEY2 0.00



//create an RF24 object
RF24 radio(9, 8);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";

float  veriler[]={KEY1,KEY2};

void setup()
{ pinMode(2,OUTPUT);
  while (!Serial);
  Serial.begin(9600); 
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  
  //Set module as receiver
  radio.startListening();

}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  
  { digitalWrite(2,HIGH);

    radio.read(veriler, sizeof(veriler));k
    
    Serial.print("Enlem:");
    Serial.print(veriler[0]);
    Serial.println();
   
    Serial.print("Boylam:");
    Serial.print(veriler[1]);
    Serial.println();
        
        
    Serial.print("Kapı Acık");
    Serial.println();
    delay(2500);
    }

    else 
    Serial.print("Kapı Kapalı");
    Serial.println();
    digitalWrite(2,LOW);
}
  
