#ifndef RB2D_F32_H
#define RB2D_F32_H

#include "rb.h"
#include "rbExtApi.h"

typedef struct {
    float32_t* buf;
    float32_t* src;
    float32_t* targetRow; // can be NULL
    float32_t* targetColumn; // can be NULL
    uint16_t pointer; // a column, point to the next empty buffer
    uint16_t numRow; // the nums of columns
    uint16_t numCol; // the nums of rows
    uint16_t lenRow; // the length of columns, equals to numCol
    uint16_t lenCol; // the length of rows, equals to numRow
    bool isHeapVer;
    bool heapValid; // reserved
} rb2d_f32_t;

void rb2d_f32_init(rb2d_f32_t* h, float32_t* buf, float32_t* src, float32_t* targetRow, float32_t* targetColumn, uint16_t numRow, uint16_t numCol);

rbStatus_t rb2d_f32_step(rb2d_f32_t* h);

rbStatus_t rb2d_f32_get_ordered_row(rb2d_f32_t* h, uint16_t row, float32_t* tar);

rbStatus_t rb2d_f32_get_unordered_row(rb2d_f32_t* h, uint16_t row, float32_t* tar);

rbStatus_t rb2d_f32_get_column(rb2d_f32_t* h, uint16_t column, float32_t* tar);

rbStatus_t rb2d_f32_get_current_column(rb2d_f32_t* h, float32_t* tar);

rbStatus_t rb2d_f32_get_oldest_column(rb2d_f32_t* h, float32_t* tar);

rbStatus_t rb2d_f32_get_value(rb2d_f32_t* h, uint16_t row, uint16_t column, float32_t* value);

void rb2d_f32_reset(rb2d_f32_t* h);

// heap version
rbStatus_t rb2d_f32_heap_init(rb2d_f32_t* h, uint16_t numRow, uint16_t numCol);

void rb2d_f32_heap_delete(rb2d_f32_t* h);

#endif
