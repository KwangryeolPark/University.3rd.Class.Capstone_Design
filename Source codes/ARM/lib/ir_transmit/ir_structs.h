/*
 * 박광렬
 * pkr7098@gmail.com
 * 2021-12-30
 * ir_structs.h
 * IR의 자료구조 
 
IR 네트워크의 자료구조에 관한 파일입니다. 
*/

#ifndef _IR_STRUCTS_H
#define _IR_STRUCTS_H

#define IR_Q_SIZE       33                                                      //      Q의 특성에 따라 총 32 개의 메시지를 보관함

struct IR_SEGMENT {
  unsigned char p_segment[250];;
  unsigned char send_id;
  unsigned char recv_id;
};

struct IR_DATAGRAM {
  unsigned char p_segment[252];                                                              //      segment data from
  unsigned char mac;
  unsigned char parity;
  unsigned char size_segment;
};

struct IR_FRAME {
  unsigned char p_datagram[255];                                                //      datagram
  unsigned char size_datagram;                                                  //      datagram size
};

// IR_FRAME
// Bits         N                       1               1               1
//              p_segment[N]    uid8            parity       size_segment
//      
void INIT_IR_FRAME(void);
int IS_IR_FRAME_EMPTY(void);
int IS_IR_FRAME_FULL(void);
int ENQUEUE_IR_FRAME(struct IR_FRAME frame);
int ENQUEUE_SUITABLE_IR_FRAME(struct IR_FRAME *frame);
int ENQUEUE_SUITABLE_IR_FRAME(struct IR_FRAME volatile *frame);
struct IR_FRAME* DEQUEUE_IR_FRAME(void);

void INIT_IR_DATAGRAM(void);
int IS_IR_DATAGRAM_EMPTY(void);
int IS_IR_DATAGRAM_FULL(void);
int ENQUEUE_IR_DATAGRAM(struct IR_DATAGRAM datagram);
int ENQUEUE_SUITABLE_IR_DATAGRAM(struct IR_DATAGRAM *datagram);
int ENQUEUE_SUITABLE_IR_DATAGRAM(struct IR_DATAGRAM volatile *datagram);
struct IR_DATAGRAM* DEQUEUE_IR_DATAGRAM(void);
#endif
