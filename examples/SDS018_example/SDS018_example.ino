// SDS018 dust sensor
// -----------------------------
//
// By L. Zhang (zhanglin.edu@outlook.com).
// August 2021

// 用排线连接：
// SDS018 --> Arduino对应管脚
//    TXD     D10
//    RXD     D11
//    GND     GND
//     5V     VCC/5V

#include <SDS018.h>

SDS018 mySDS;
SoftwareSerial mySerial(10, 11); //Pin 11 == RX, Pin 10 == TX

void setup() {
  mySerial.begin(9600);
  mySDS.begin(&mySerial);
  Serial.begin(9600);
}
float pm2_5 = -1.0, pm10 = -1.0;

void loop() {
  int len = 0;
  mySDS.query();
  mySDS.read_float(&pm2_5, &pm10);
  Serial.println("PM 2.5: " + String(pm2_5));
  Serial.println("PM 10 :  " + String(pm10));
  delay(1000);
}
