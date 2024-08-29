#include "rb2d_f32.h"
#include "rb.h"
#include "rbExtApi.h"
#include <stdbool.h>

static rbStatus_t _rb2d_f32_valid_check(rb2d_f32_t* h) {
    if (h->buf == NULL) {
        return rbStatusErr;
    }
    if (h->isHeapVer && !h->heapValid) {
        return rbStatusErr;
    }
    return rbStatusOK;
}

static void _rb2d_f32_get_column_idx(rb2d_f32_t* h, int16_t* column) {
    *column = h->pointer - *column - 1;  // return to previous
    if (*column < 0) {
        *column += h->numCol;
    }
}

void rb2d_f32_init(rb2d_f32_t* h, float32_t* buf, float32_t* src, float32_t* targetRow, float32_t* targetColumn, uint16_t numRow, uint16_t numCol) {
    h->buf = buf;
    h->src = src;
    h->targetRow = targetRow;
    h->targetColumn = targetColumn;
    h->pointer = 0;
    h->numRow = numRow;  // [10, 20] -> [numRow, numCol]
    h->numCol = numCol;  // numRow == lenCol
    h->lenRow = numCol;
    h->lenCol = numRow; 
    h->isHeapVer = false;
    memset((void*)h->buf, 0, h->numRow * h->numCol * sizeof(float32_t));
}

rbStatus_t rb2d_f32_step(rb2d_f32_t* h) {
    if (_rb2d_f32_valid_check(h) != rbStatusOK) {
        return rbStatusErr;
    }
    memmove((void*)&h->buf[h->lenCol * h->pointer++], (void*)h->src, sizeof(float32_t) * h->lenCol);
    if (h->pointer >= h->lenRow) {
        h->pointer = 0;
    }
    return rbStatusOK;
}

rbStatus_t rb2d_f32_get_ordered_row(rb2d_f32_t* h, uint16_t row, float32_t* tar) {
    if (_rb2d_f32_valid_check(h) != rbStatusOK) {
        return rbStatusErr;
    }
    int part2bias = h->lenRow - h->pointer;
    if (tar == NULL) {
        for (int i = h->pointer; i < h->lenRow; i++) {
            h->targetRow[i - h->pointer] = h->buf[h->lenCol * i + row];
        }
        for (int i = 0; i < h->pointer; i++) {
            h->targetRow[part2bias + i] = h->buf[h->lenCol * i + row];
        }
    } else {
        for (int i = h->pointer; i < h->lenRow; i++) {
            tar[i - h->pointer] = h->buf[h->lenCol * (h->pointer + i) + row];
        }
        for (int i = 0; i < h->pointer; i++) {
            tar[part2bias + i] = h->buf[h->lenCol * i + row];
        }
    }
    return rbStatusOK;
}

rbStatus_t rb2d_f32_get_unordered_row(rb2d_f32_t* h, uint16_t row, float32_t* tar) {
    if (_rb2d_f32_valid_check(h) != rbStatusOK) {
        return rbStatusErr;
    }
    if (tar == NULL) {
        for (int i = 0; i < h->lenRow; i++) {
            h->targetRow[i] = h->buf[h->lenCol * i + row];
        }
    } else {
        for (int i = 0; i < h->lenRow; i++) {
            tar[i] = h->buf[h->lenCol * i + row];
        }
    }
    return rbStatusOK;
}

rbStatus_t rb2d_f32_get_column(rb2d_f32_t* h, uint16_t column, float32_t* tar) {
    if (_rb2d_f32_valid_check(h) != rbStatusOK) {
        return rbStatusErr;
    }
    _rb2d_f32_get_column_idx(h, (int16_t*)&column);
    if (tar == NULL) {
        memmove((void*)h->targetColumn, &h->buf[column * h->lenCol], sizeof(float32_t) * h->lenCol);
    } else {
        memmove((void*)tar, &h->buf[column * h->lenCol], sizeof(float32_t) * h->lenCol);
    }
    return rbStatusOK;
}

// the definition of the column index:
// current -> 0, previous1 -> 1, previous2 -> 2, ... oldest -> h->numCol - 1

rbStatus_t rb2d_f32_get_current_column(rb2d_f32_t* h, float32_t* tar) {
    if (rb2d_f32_get_column(h, 0, tar) != rbStatusOK) {
        return rbStatusErr;
    }
    return rbStatusOK;
}

rbStatus_t rb2d_f32_get_oldest_column(rb2d_f32_t* h, float32_t* tar) {
    if (rb2d_f32_get_column(h, h->numCol - 1, tar) != rbStatusOK) {
        return rbStatusErr;
    }
    return rbStatusOK;
}

rbStatus_t rb2d_f32_get_value(rb2d_f32_t* h, uint16_t row, uint16_t column, float32_t* value) {
    if (_rb2d_f32_valid_check(h) != rbStatusOK) {
        return rbStatusErr;
    }
    _rb2d_f32_get_column_idx(h, (int16_t*)&column);
    *value = h->buf[column * h->lenCol + row];
    return rbStatusOK;
}

void rb2d_f32_reset(rb2d_f32_t* h) {
    h->pointer = 0;
    if (h->isHeapVer && !h->heapValid) {
        return;
    }
    memset((void*)h->buf, 0, sizeof(float32_t) * h->numRow * h->numCol);
    memset((void*)h->src, 0, sizeof(float32_t) * h->numCol);
    if (h->targetRow != NULL) {
        memset((void*)h->targetRow, 0, sizeof(float32_t) * h->numRow);
    }
    if (h->targetColumn != NULL) {
        memset((void*)h->targetColumn, 0, sizeof(float32_t) * h->numCol);
    }
}

// heap version
rbStatus_t rb2d_f32_heap_init(rb2d_f32_t* h, uint16_t numRow, uint16_t numCol) {
    h->buf = (float32_t*) rbLibMalloc(sizeof(float32_t) * numCol * numRow);
    if (h->buf == NULL) {
        return rbStatusErr;
    }
    h->src = (float32_t*) rbLibMalloc(sizeof(float32_t) * numRow);
    if (h->src == NULL) {
        return rbStatusErr;
    }
    h->targetRow = (float32_t*) rbLibMalloc(sizeof(float32_t) * numCol);
    if (h->targetRow == NULL) {
        return rbStatusErr;
    }
    h->targetColumn = (float32_t*) rbLibMalloc(sizeof(float32_t) * numRow);
    if (h->targetColumn == NULL) {
        return rbStatusErr;
    }
    h->pointer = 0;
    h->numRow = numRow;  // [10, 20] -> [numRow, numCol]
    h->numCol = numCol;  // numRow == lenCol
    h->lenRow = numCol;
    h->lenCol = numRow;
    h->isHeapVer = true;
    h->heapValid = true;
    memset((void*)h->buf, 0, h->numRow * h->numCol * sizeof(float32_t));
    return rbStatusOK;
}

void rb2d_f32_heap_delete(rb2d_f32_t* h) {
    rbLibFree(h->buf);
    h->heapValid = false;
}
