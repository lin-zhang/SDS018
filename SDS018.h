

/*  SDS018 dust sensor PM2.5 and PM10
    ---------------------

   By L. ZHANG (zhanglin.edu@outlook.com)
    August 2021
*/

#ifndef __SDS018_H
#define __SDS018_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <SoftwareSerial.h>


class SDS018 {
  public:
    SDS018(void);

    void begin(SoftwareSerial* serial);
    void begin(uint8_t pin_rx, uint8_t pin_tx);

    int read_float(float *p25, float *p10);
    void continuous_mode();
    void query();
  private:
    uint8_t _pin_rx, _pin_tx;
    Stream *sds_data;
};

#endif
