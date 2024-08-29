#include "rb1d_int16.h"

void rb1d_int16_init(rb1d_int16_t* h, int16_t* arr, uint16_t len, bool sumEnable) {
    h->arr = arr;
    h->sum = 0;
    h->pointer = 0;
    h->len = len;
    h->sumEnable = sumEnable;
    h->isHeapVer = false;
    memset(h->arr, 0, h->len * sizeof(int16_t));
}

void rb1d_int16_step(rb1d_int16_t* h, int16_t value) {  // heap multiplexing
    if (h->sumEnable) {
        h->sum -= h->arr[h->pointer];
        h->sum += value;
    }
    h->arr[h->pointer++] = value;
    if (h->pointer >= h->len) {
        h->pointer = 0;
    }
}

rbStatus_t rb1d_int16_get_ordered_arr(rb1d_int16_t* h, int16_t* arr) {  // heap multiplexing
    if (arr == NULL) {
        return rbStatusErr;
    }
    memmove((void*)arr, (void*)&h->arr[h->pointer], sizeof(int16_t) * (h->len - h->pointer));
    if (h->pointer != 0) {
        memmove((void*)&arr[h->len - h->pointer], h->arr, sizeof(int16_t) * h->pointer);
    }
    return rbStatusOK;
}

void rb1d_int16_reset(rb1d_int16_t* h) {  // heap multiplexing
    h->sum = 0;
    h->pointer = 0;
    if (h->isHeapVer && !h->heapValid) {
        return;
    }
    memset(h->arr, 0, h->len * sizeof(int16_t));
}

//heap version
rbStatus_t rb1d_int16_heap_init(rb1d_int16_t* h, uint16_t len, bool sumEnable) {
    h->arr = (int16_t*)rbLibMalloc(sizeof(int16_t) * len);
    if (h->arr == NULL) {
        h->heapValid = false;
        return rbStatusErr;
    }
    h->sum = 0;
    h->pointer = 0;
    h->len = len;
    h->sumEnable = sumEnable;
    h->isHeapVer = true;
    h->heapValid = true;
    memset(h->arr, 0, h->len * sizeof(int16_t));
    return rbStatusOK;
}

void rb1d_int16_heap_delete(rb1d_int16_t* h) {
    rbLibFree((void*)h->arr);
    h->sum = 0;
    h->pointer = 0;
    h->heapValid = false;
}
