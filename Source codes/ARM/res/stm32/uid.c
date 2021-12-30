/*
 * ¹Ú±¤·Ä
 * pkr7098@gmail.com
 * 2021-12-29
 * uid.c
 * Unique Identifier °ü·Ã 
 
*/

#include "uid.h"

volatile struct _UID *UID = (struct _UID *) 0x1FFFF7E8;

uint8_t UID_GET_BYTE(uint8_t UID_STEP) {
  if (UID_STEP == 0) {
    return (uint8_t) UID -> U_ID0;
  }
  if (UID_STEP == 1) {
    return (uint8_t) UID -> U_ID1;
  }
  if (UID_STEP == 2) {
    return (uint8_t) UID -> U_ID2;
  }
  return (uint8_t) UID -> U_ID0;
}

uint16_t UID_GET_HALF_WORD(uint8_t UID_STEP) {
  if (UID_STEP == 0) {
    return (uint16_t) UID -> U_ID0;
  }
  if (UID_STEP == 1) {
    return (uint16_t) UID -> U_ID1;
  }
  if (UID_STEP == 2) {
    return (uint16_t) UID -> U_ID2;
  }
  return (uint16_t) UID -> U_ID0;
}

uint32_t UID_GET_WORD(uint8_t UID_STEP) {
  if (UID_STEP == 0) {
    return (uint32_t) UID -> U_ID0;
  }
  if (UID_STEP == 1) {
    return (uint32_t) UID -> U_ID1;
  }
  if (UID_STEP == 2) {
    return (uint32_t) UID -> U_ID2;
  }
  return (uint32_t) UID -> U_ID0;
}

