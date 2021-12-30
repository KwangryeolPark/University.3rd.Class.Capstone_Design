#include "ir_structs.h"

struct IR_FRAME IR_QUEUE_FRAME[IR_Q_SIZE];

static int IR_FRAME_FRONT;
static int IR_FRAME_REAR;

void INIT_IR_FRAME(void) {
  IR_FRAME_FRONT = 0;
  IR_FRAME_REAR = 0;  
}

int IS_IR_FRAME_EMPTY(void) {
  return IR_FRAME_FRONT == IR_FRAME_REAR ? 1 : 0;
}

int IS_IR_FRAME_FULL(void) {
  return ((IR_FRAME_REAR + 1) % IR_Q_SIZE) == IR_FRAME_FRONT ? 1 : 0;
}

int ENQUEUE_IR_FRAME(struct IR_FRAME frame) {
  int return_value = 0;
  if (IS_IR_FRAME_FULL()) {
    DEQUEUE_IR_FRAME();
    return_value = 1;
  }
  
  IR_QUEUE_FRAME[(++IR_FRAME_REAR) % IR_Q_SIZE] = frame;
  return return_value;
}

struct IR_FRAME* DEQUEUE_IR_FRAME(void) {
  if (!IS_IR_FRAME_EMPTY()) {
    return &IR_QUEUE_FRAME[(++IR_FRAME_FRONT) % IR_Q_SIZE];
  } else {
    return (struct IR_FRAME*) 0;
  }
}
