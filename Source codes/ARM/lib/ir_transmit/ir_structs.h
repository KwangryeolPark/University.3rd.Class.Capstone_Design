#ifndef _IR_STRUCTS_H
#define _IR_STRUCTS_H

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
  void *p_datagram;             //      datagram
  unsigned char size_datagram;  //      datagram size
};


#endif