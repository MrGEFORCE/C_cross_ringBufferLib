#ifndef RB1D_UINT16_H
#define RB1D_UINT16_H

#include "rb.h"

typedef struct {
    uint16_t* arr;
    uint32_t sum;
    uint16_t pointer;
    uint16_t len;
    bool sumEnable;
    bool isHeapVer;
    bool heapValid;
} rb1d_uint16_t;

void rb1d_uint16_init(rb1d_uint16_t* h, uint16_t* arr, uint16_t len, bool sumEnable);

void rb1d_uint16_step(rb1d_uint16_t* h, uint16_t value);

rbStatus_t rb1d_uint16_get_ordered_arr(rb1d_uint16_t* h, uint16_t* arr);

void rb1d_uint16_reset(rb1d_uint16_t* h);

// heap version
rbStatus_t rb1d_uint16_heap_init(rb1d_uint16_t* h, uint16_t len, bool sumEnable);

void rb1d_uint16_heap_delete(rb1d_uint16_t* h);

#endif
