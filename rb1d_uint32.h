#ifndef RB1D_UINT32_H
#define RB1D_UINT32_H

#include "rb.h"

typedef struct {
    uint32_t* arr;
    uint32_t sum;
    uint16_t pointer;
    uint16_t len;
    bool sumEnable;
    bool isHeapVer;
    bool heapValid;
} rb1d_uint32_t;

void rb1d_uint32_init(rb1d_uint32_t* h, uint32_t* arr, uint16_t len, bool sumEnable);

void rb1d_uint32_step(rb1d_uint32_t* h, uint32_t value);

rbStatus_t rb1d_uint32_get_ordered_arr(rb1d_uint32_t* h, uint32_t* arr);

void rb1d_uint32_reset(rb1d_uint32_t* h);

// heap version
rbStatus_t rb1d_uint32_heap_init(rb1d_uint32_t* h, uint16_t len, bool sumEnable);

void rb1d_uint32_heap_delete(rb1d_uint32_t* h);

#endif
