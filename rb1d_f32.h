#ifndef RB1D_F32_H
#define RB1D_F32_H

#include "rb.h"

typedef struct {
    float32_t* arr;
    float32_t sum;
    uint16_t pointer;
    uint16_t len;
    bool sumEnable;
    bool isHeapVer;
    bool heapValid;
} rb1d_f32_t;

void rb1d_f32_init(rb1d_f32_t* h, float32_t* arr, uint16_t len, bool sumEnable);

void rb1d_f32_step(rb1d_f32_t* h, float32_t value);

rbStatus_t rb1d_f32_get_ordered_arr(rb1d_f32_t* h, float32_t* arr);

void rb1d_f32_reset(rb1d_f32_t* h);

// heap version
rbStatus_t rb1d_f32_heap_init(rb1d_f32_t* h, uint16_t len, bool sumEnable);

void rb1d_f32_heap_delete(rb1d_f32_t* h);

#endif
