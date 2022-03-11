/*
 * 박광렬
 * pkr7098@gmail.com
 * 2021-12-30
 * ir_structs.c
 * IR의 자료구조 
 
IR 네트워크의 자료구조에 관한 파일입니다. 
*/

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

int ENQUEUE_SUITABLE_IR_FRAME(struct IR_FRAME *frame) {
  struct IR_FRAME *target;
  int return_value = 0;
  if (IS_IR_FRAME_FULL()) {
    DEQUEUE_IR_FRAME();
    return_value = 1;
  }
  
  target = &IR_QUEUE_FRAME[(++IR_FRAME_REAR) % IR_Q_SIZE];
  
  
  target -> size_datagram = frame -> size_datagram;
  
  for (int i = 0; i < frame -> size_datagram; i++) {
    (target -> p_datagram)[i] = (frame -> p_datagram)[i];
  }
  return return_value;
}

int ENQUEUE_SUITABLE_IR_FRAME(struct IR_FRAME volatile *frame) {
  struct IR_FRAME *target;
  int return_value = 0;
  if (IS_IR_FRAME_FULL()) {
    DEQUEUE_IR_FRAME();
    return_value = 1;
  }
  
  target = &IR_QUEUE_FRAME[(++IR_FRAME_REAR) % IR_Q_SIZE];
  
  
  target -> size_datagram = frame -> size_datagram;
  
  for (register int i = 0; i < frame -> size_datagram; i++) {
    (target -> p_datagram)[i] = (frame -> p_datagram)[i];
  }
  return return_value;
}

struct IR_FRAME* DEQUEUE_IR_FRAME(void) {
  if (!IS_IR_FRAME_EMPTY()) {
    return &IR_QUEUE_FRAME[(++IR_FRAME_FRONT) % IR_Q_SIZE];
  } else {
    return (struct IR_FRAME*) 0;
  }
}

////////////////////////////////////////////////////////////////////

struct IR_DATAGRAM IR_QUEUE_DATAGRAM[IR_Q_SIZE];

static int IR_DATAGRAM_FRONT;
static int IR_DATAGRAM_REAR;

void INIT_IR_DATAGRAM(void) {
  IR_DATAGRAM_FRONT = 0;
  IR_DATAGRAM_REAR = 0;  
}

int IS_IR_DATAGRAM_EMPTY(void) {
  return IR_DATAGRAM_FRONT == IR_DATAGRAM_REAR ? 1 : 0;
}

int IS_IR_DATAGRAM_FULL(void) {
  return ((IR_DATAGRAM_REAR + 1) % IR_Q_SIZE) == IR_DATAGRAM_FRONT ? 1 : 0;
}

int ENQUEUE_IR_DATAGRAM(struct IR_DATAGRAM datagram) {
  int return_value = 0;
  if (IS_IR_DATAGRAM_FULL()) {
    DEQUEUE_IR_DATAGRAM();
    return_value = 1;
  }
  
  IR_QUEUE_DATAGRAM[(++IR_DATAGRAM_REAR) % IR_Q_SIZE] = datagram;
  return return_value;
}

int ENQUEUE_SUITABLE_IR_DATAGRAM(struct IR_DATAGRAM *datagram) {
  struct IR_DATAGRAM *target;
  int return_value = 0;
  if (IS_IR_DATAGRAM_FULL()) {
    DEQUEUE_IR_DATAGRAM();
    return_value = 1;
  }
  
  target = &IR_QUEUE_DATAGRAM[(++IR_DATAGRAM_REAR) % IR_Q_SIZE];
  
  
  target -> mac = datagram -> mac;
  target -> parity = datagram -> parity;
  target -> size_segment = datagram -> size_segment;
  
  for (int i = 0; i < datagram -> size_segment; i++) {
    (target -> p_segment)[i] = (datagram -> p_segment)[i];
  }
  return return_value;
}

int ENQUEUE_SUITABLE_IR_DATAGRAM(struct IR_DATAGRAM volatile *datagram) {
  struct IR_DATAGRAM *target;
  int return_value = 0;
  if (IS_IR_DATAGRAM_FULL()) {
    DEQUEUE_IR_DATAGRAM();
    return_value = 1;
  }
  
  target = &IR_QUEUE_DATAGRAM[(++IR_DATAGRAM_REAR) % IR_Q_SIZE];
  
  
  target -> mac = datagram -> mac;
  target -> parity = datagram -> parity;
  target -> size_segment = datagram -> size_segment;
  
  for (register int i = 0; i < datagram -> size_segment; i++) {
    (target -> p_segment)[i] = (datagram -> p_segment)[i];
  }
  return return_value;
}

struct IR_DATAGRAM* DEQUEUE_IR_DATAGRAM(void) {
  if (!IS_IR_DATAGRAM_EMPTY()) {
    return &IR_QUEUE_DATAGRAM[(++IR_DATAGRAM_FRONT) % IR_Q_SIZE];
  } else {
    return (struct IR_DATAGRAM*) 0;
  }
}