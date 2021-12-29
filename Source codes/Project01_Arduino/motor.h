#ifndef _MOTOR_H
#define _MOTOR_H

#include "Configuration.h"

#ifdef  _CHANNEL_A
#error  "_CHANNEL_A is already defined!!"
#else
#define _CHANNEL_A  1
#endif

#ifdef  _CHANNEL_B
#error  "_CHANNEL_B is already defined!!"
#else
#define _CHANNEL_B  2
#endif

#ifdef  BRAKE
#error  "BRAKE is already defined!!"
#else
#define BRAKE 1
#endif

#ifdef  NON_BRAKE
#error  "NON_BRAKE is already defined!!"
#else
#define NON_BRAKE 0
#endif

class Motor {
  public:
    Motor(void);
    void init(uint8_t);
    void act(int16_t, int16_t);
    void stop(void);
    void mode(uint8_t);

  private:
    int16_t _SPD_A, _SPD_B;
    uint8_t _MODE;

    void rotate(uint8_t, int16_t);
};

Motor::Motor(void) {
  
};

void Motor::rotate(uint8_t channel, int16_t spd) {
  uint8_t IN1, IN2;
  switch (channel) {
    case _CHANNEL_A:
      IN1 = MOTOR_AIN2;
      IN2 = MOTOR_AIN1;
      break;

    case _CHANNEL_B:
      IN1 = MOTOR_BIN1;
      IN2 = MOTOR_BIN2;
      break;
  }

  if (_MODE == NON_BRAKE) {
    if (spd > 0) {
      analogWrite(IN1, spd);
      digitalWrite(IN2, 0);
    } else if (spd == 0) {
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 0);
    } else {
      digitalWrite(IN1, 0);
      analogWrite(IN2, -spd);
    }
  } else {
    if (spd > 0) {
      digitalWrite(IN1, 1);
      analogWrite(IN2, 255 - spd);
    } else if (spd == 0) {
      digitalWrite(IN1, 1);
      digitalWrite(IN2, 1);
    } else {
      analogWrite(IN1, 255 + spd);
      digitalWrite(IN2, 1);
    }
  }
};

void Motor::init(uint8_t mode) {
  _MODE = mode;

  digitalWrite(MOTOR_AIN1, 0);
  digitalWrite(MOTOR_AIN2, 0);
  digitalWrite(MOTOR_BIN1, 0);
  digitalWrite(MOTOR_BIN2, 0);

  pinMode(MOTOR_AIN1, OUTPUT);
  pinMode(MOTOR_AIN2, OUTPUT);
  pinMode(MOTOR_BIN1, OUTPUT);
  pinMode(MOTOR_BIN2, OUTPUT);
};

void Motor::act(int16_t spd_a, int16_t spd_b) {
  rotate(_CHANNEL_A, _SPD_A = spd_a);
  rotate(_CHANNEL_B, _SPD_B = spd_b);
};

void Motor::stop(void) {
  rotate(_CHANNEL_A, _SPD_A = 0);
  rotate(_CHANNEL_B, _SPD_B = 0);
};

void Motor::mode(uint8_t mode) {
  _MODE = mode;
};

#endif
