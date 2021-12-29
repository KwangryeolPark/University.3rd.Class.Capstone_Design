#include "location.h"
#include "motor.h"
#include "pid.h"
#include "astar.h"

Motor motor;

void setup() {
  // put your setup code here, to run once:
  motor.init(BRAKE);
}

/*int16_t sequence[4][2] = {
  {100, 100},

  }*/

void loop() {
  // put your main code here, to run repeatedly:
  motor.act(127, 127);

  for (int16_t i = 0; i < 127; i += 1) {
    motor.act(i, i);
    delay(2000 / 127);
  }
  for (int16_t i = 126; i >= 0; i -= 1) {
    motor.act(i, i);
    delay(2000 / 127);
  }
  motor.stop();
  delay(1000);
  for (int16_t i = 0; i < 127; i += 1) {
    motor.act(i, -i);
    delay(2000 / 127);
  }
  for (int16_t i = 126; i >= 0; i -= 1) {
    motor.act(i, -i);
    delay(2000 / 127);
  }
  delay(1000);
  motor.stop();
  delay(1000);
}
