#ifndef RB1D_INT8_H
#define RB1D_INT8_H

#include "rb.h"

typedef struct {
    int8_t* arr;
    int32_t sum;
    uint16_t pointer;
    uint16_t len;
    bool sumEnable;
    bool isHeapVer;
    bool heapValid;
} rb1d_int8_t;

void rb1d_int8_init(rb1d_int8_t* h, int8_t* arr, uint16_t len, bool sumEnable);

void rb1d_int8_step(rb1d_int8_t* h, int8_t value);

rbStatus_t rb1d_int8_get_ordered_arr(rb1d_int8_t* h, int8_t* arr);

void rb1d_int8_reset(rb1d_int8_t* h);

// heap version
rbStatus_t rb1d_int8_heap_init(rb1d_int8_t* h, uint16_t len, bool sumEnable);

void rb1d_int8_heap_delete(rb1d_int8_t* h);

#endif
