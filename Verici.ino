#include <SoftwareSerial.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
SoftwareSerial GPS(0, 1); // Rx, Tx
RF24 radio(9, 8);  // CE, CSN

String saat = "";    // hhmmss.00
String enlem = "";   // DDMM.MMMM Kuzey/Güney N/S
String boylam = "";  // DDMM.MMMM Doğu/Batı E/W
String irtifa = "";  // metre
const byte address[6] = "00001";
float veriler[2];
void setup() {
  Serial.begin(9600);
  GPS.begin(9600);
  
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  
  //Set module as transmitter
  radio.stopListening();
}

void loop() {

  GPSdinle();

  Serial.print("Saat: ");
  Serial.println(saat);
  Serial.print("Enlem: ");
  Serial.println(enlem);
  Serial.print("Boylam: ");
  Serial.println(boylam);
  Serial.print("irtifa: ");
  Serial.println(irtifa);
  Serial.println();
  
  veriler[0] = enlem.substring(0, 8).toFloat();
  veriler[1] = boylam.substring(0, 8).toFloat();
 


  

  Serial.print(veriler[0]);
  Serial.println();
  Serial.print(veriler[1]);
  Serial.println();


  radio.write(veriler, sizeof(veriler));
}

void GPSdinle() {

  // $GPGGA arıyoruz
  if ( GPS.find("$GPGGA,") ) {

    // Gelen veriyi parçalıyoruz
    saat = GPS.readStringUntil(',');
    enlem = GPS.readStringUntil(',');
    enlem.concat(GPS.readStringUntil(','));
    boylam = GPS.readStringUntil(',');
    boylam.concat(GPS.readStringUntil(','));

    // irtifaya kadar olan kısmı atlıyoruz
    for ( int i = 0; i < 3; i++ ) {
      GPS.readStringUntil(',');
    }

    // irtifa verisini parçala
    irtifa = GPS.readStringUntil(',');
    irtifa.concat(GPS.readStringUntil(','));

    // Verinin geri kalanını atlıyoruz
    GPS.readStringUntil('\r');
  }
}
