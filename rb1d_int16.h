#ifndef RB1D_INT16_H
#define RB1D_INT16_H

#include "rb.h"

typedef struct {
    int16_t* arr;
    int32_t sum;
    uint16_t pointer;
    uint16_t len;
    bool sumEnable;
    bool isHeapVer;
    bool heapValid;
} rb1d_int16_t;

void rb1d_int16_init(rb1d_int16_t* h, int16_t* arr, uint16_t len, bool sumEnable);

void rb1d_int16_step(rb1d_int16_t* h, int16_t value);

rbStatus_t rb1d_int16_get_ordered_arr(rb1d_int16_t* h, int16_t* arr);

void rb1d_int16_reset(rb1d_int16_t* h);

// heap version
rbStatus_t rb1d_int16_heap_init(rb1d_int16_t* h, uint16_t len, bool sumEnable);

void rb1d_int16_heap_delete(rb1d_int16_t* h);

#endif
