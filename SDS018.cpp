/*  SDS018 dust sensor PM2.5 and PM10
    ---------------------

   By L. ZHANG (zhanglin.edu@outlook.com)
    August 2021
*/

#include "SDS018.h"

static constexpr
uint8_t CONTINUOUS_MODE_CMD[] PROGMEM = {
  0xAA, 0xB4, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,
  0xFF, 0x07, 0xAB
};

uint8_t QUERY_MODE_CMD[8] = {
  0xC0, 0x03, 0x00, 0xB4, 0x00, 0x02, 0x94, 0xFC
};

SDS018::SDS018(void) {
}

static
uint16_t PM25_CRC16(uint8_t *Buf , uint32_t usLen)  {
  uint16_t  i, j;
  uint16_t usCrc = 0xFFFF;
  for ( i = 0 ; i < usLen ; i++ ) {
    usCrc ^= Buf[i];
    for ( j = 0 ; j < 8 ; j++ ) {
      if ( usCrc & 1 ) {
        usCrc >>= 1;
        usCrc ^= 0xA001;
      } else {
        usCrc >>= 1;
      }
    }
  }
  return usCrc;
}

// --------------------------------------------------------
// SDS018:query and read
// --------------------------------------------------------

int SDS018::read_float(float *p25, float *p10) {

  static uint8_t result[9];
  int char_cnt = 0;

  while ((sds_data->available() > 0) && char_cnt < 9) {
    result[char_cnt++] = sds_data->read();
  }
  if (result[0] == 0xC0) {
    uint16_t crc_pm;
    uint16_t crc_msg;
    crc_pm = PM25_CRC16(result, 7);
    crc_msg = result[8] * 256 + result[7];
    if (crc_pm == crc_msg) {
      *p25 = (result[4] + result[3] * 256) / 10.0;
      *p10 = (result[6] + result[5] * 256) / 10.0;
    }
  }
}

void SDS018::query() {
  for (uint8_t i = 0; i < 8; i++) {
    sds_data->write(QUERY_MODE_CMD[i]);
  }
  sds_data->flush();
}

void SDS018::begin(uint8_t pin_rx, uint8_t pin_tx) {
    _pin_rx = pin_rx;
    _pin_tx = pin_tx;

    SoftwareSerial *softSerial = new SoftwareSerial(_pin_rx, _pin_tx);

    softSerial->begin(9600);

    sds_data = softSerial;
}

void SDS018::begin(SoftwareSerial* serial) {
    serial->begin(9600);
    sds_data = serial;
}
