#ifndef _IR_STRUCTS_H
#define _IR_STRUCTS_H

#define IR_Q_SIZE       32

struct IR_SEGMENT {
  unsigned char send_id;
  unsigned char recv_id;
  char *p_msg;
};

struct IR_DATAGRAM {
  void *p_segment;              //      segment data from
  unsigned char parity;
  unsigned char size_segment;
};

struct IR_FRAME {
  unsigned char p_datagram[255];             //      datagram
  unsigned char size_datagram;  //      datagram size
};


void INIT_IR_FRAME(void);
int IS_IR_FRAME_EMPTY(void);
int IS_IR_FRAME_FULL(void);
int ENQUEUE_IR_FRAME(struct IR_FRAME frame);
struct IR_FRAME* DEQUEUE_IR_FRAME(void);

#endif