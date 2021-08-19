# SDS018
  
Arduino library for dust Sensor SDS018 (Nova Fitness Co.,Ltd)  
This library uses SoftSerial ONLY to connect to the SDS018.  
  
## Usage

* Define SDS object:
i.e. ```SDS018 mySDS;```
  
* Start object:
```void begin(pinRX,pinTX);```
i.e. ```mySDS.begin(pinRX,pinTX);```
  
* Query and read values:
```int query(void);```
```int read(float *pm25, float *pm10);```
