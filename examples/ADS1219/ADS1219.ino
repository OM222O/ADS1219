#include <Wire.h>
#include <ADS1219.h>
#define address 0x40
#define rst 14
#define drdy 15

ADS1219 ads(drdy);



void setup() {
  ads.begin();
  pinMode(drdy,INPUT_PULLUP);
  pinMode(rst,OUTPUT);
  digitalWrite(rst,HIGH);
  Wire.begin();
  Serial.begin(9600);
  ads.setVoltageReference(REF_EXTERNAL);
}

void loop() {
  Serial.println("Single ended result:");
  Serial.println(ads.readSingleEnded(2)*2.048/pow(2,23),5);
  delay(2000);
  Serial.println("Differential result:");
  Serial.println(ads.readDifferential_2_3()*2.048/pow(2,23),5);
  delay(2000);
}
