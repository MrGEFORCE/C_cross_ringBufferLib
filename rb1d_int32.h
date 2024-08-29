#ifndef RB1D_INT32_H
#define RB1D_INT32_H

#include "rb.h"

typedef struct {
    int32_t* arr;
    int32_t sum;
    uint16_t pointer;
    uint16_t len;
    bool sumEnable;
    bool isHeapVer;
    bool heapValid;
} rb1d_int32_t;

void rb1d_int32_init(rb1d_int32_t* h, int32_t* arr, uint16_t len, bool sumEnable);

void rb1d_int32_step(rb1d_int32_t* h, int32_t value);

rbStatus_t rb1d_int32_get_ordered_arr(rb1d_int32_t* h, int32_t* arr);

void rb1d_int32_reset(rb1d_int32_t* h);

// heap version
rbStatus_t rb1d_int32_heap_init(rb1d_int32_t* h, uint16_t len, bool sumEnable);

void rb1d_int32_heap_delete(rb1d_int32_t* h);

#endif
