/*
   IR로 CSMA-CA를 구현해야함.


*/



#ifndef _IR_H
#define _IR_H

#include "Configuration.h"
#include <IRremote.h>
#include <IRremoteInt.h>

#ifdef DETECTED
#error "DETECTED is already defined!!"
#else
#define DETECTED  1
#endif

#define FAILED  10
#define OKAY  0

#define RTC 0xFF00
#define CTS 0xFF10
#define ACK 0xFFFF

uint16_t  disTbl[] = {
  920,  //  25mm
  555,  //  35mm
  370,
  240,
  180,
  155,
  130,
  115,
  105,
  93    //  115mm
};

class IR {
  public:
    IR(void);
    void init(void);
    void setIterCnt(uint8_t);

    bool isDetected(void);
    uint16_t state(void);
    uint8_t send(char *buf);
    void recogCTS(void);

  private:
    IRrecv irrecv(IR_RECEIVE);
    IRsend irsend(IR_TRANSMIT);
    uint8_t _iterCnt = 50;
    bool _state;
    uint32_t _backOff = 0;
}

IR::IR(void) {

};

void IR::init(void) {
  irrecv.enableIRIn();
  _iterCnt = 50;
  _state = 1;           //  Send okay
  _baskOff = 0;
};

void IR::iterCnt(uint8_t iterCnt) {
  _iterCnt = iterCnt;
};

bool IR::isDetected(void) {
  if (state() < 90) {
    return !DETECTED;
  }
  return DETECTED;
};

uint16_t state(void) {
  uint32_t sum = 0;
  for (int i = 0; i < iterCnt; i++) {
    sum += analogRead(IR_RECEIVE);
  }
  return sum / iterCnt;
}

uint8_t send(char *buf, uint8_t id) {
  decode_results res;
  int i;
  unsigned long time;
  if (_state == 1) {
    while (isDetected()) {
      _backOff++;
      if (_backOff == 11) {
        return FAILED;
      }
      int ran = random(pow(2, _backOff));
      delay(ran);
    }



    for (i = 0; i < 5; i++) {
      irsend.sendNEC(RTS);
      irsend.sendNEC(id);
      time = millis();
      while (1) {
        if (irrecv.decode(&res)) {
          if (res.value == CTS) {
            i = 10;
            break;
          }
        }
        if (millis() - time > 2000) {
          return FAILED;
        }
      }
    }
    if (i != 10) {
      return FAILED;
    }



    while (buf != null) {
      irsend.sendNEC(*buf);
      buf++;
    }

    return OKAY;
  }
  return FAILED;
};

void IR::recogCTS(void) {
  decode_results res;
  if (irrecv.decode(&res)) {
    if (res.value == CTS) {
      _state = 0;
      return;
    }
  }
  _state = 1;
};



#endif
