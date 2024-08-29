#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "rb1d_f32.h"
#include "rb2d_f32.h"
#include "rb1d_int32.h"
#include "rbExtApi.h"

rb1d_f32_t rb1d_f32_testHandler;
float32_t rb1d_f32_arr[10];
float32_t rb1d_f32_orderedArr[10];

rb1d_int32_t rb1d_int32_testHandler;
int32_t rb1d_int32_arr[10];
int32_t rb1d_int32_orderedArr[10];

rb2d_f32_t rb2d_f32_testHandler;
float32_t rb2d_f32_arr[10][20];
float32_t rb2d_f32_src[20];
float32_t rb2d_f32_col[20];
float32_t rb2d_f32_row[10];

//#define TEST_F32
//#define TEST_INT32
#define TEST_F32_2D

// only for test, not in the lib
int main() {

    // test for f32
#ifdef TEST_F32
    rb1d_f32_init(&rb1d_f32_testHandler, rb1d_f32_arr, 10, true);

    for (int i=0;i<15;i++) {
        rb1d_f32_step(&rb1d_f32_testHandler, (float32_t)i);
    }

    rb1d_f32_get_ordered_arr(&rb1d_f32_testHandler, rb1d_f32_orderedArr);

    rb1d_f32_heap_init(&rb1d_f32_testHandler, 10, true);

    for (int i=0;i<15;i++) {
        rb1d_f32_step(&rb1d_f32_testHandler, (float32_t)i);
    }

    rb1d_f32_get_ordered_arr(&rb1d_f32_testHandler, rb1d_f32_orderedArr);

    rb1d_f32_heap_delete(&rb1d_f32_testHandler);
#endif

    // test for int32
#ifdef TEST_INT32
    rb1d_int32_init(&rb1d_int32_testHandler, rb1d_int32_arr, 10, true);

    for (int i=0;i<15;i++) {
        rb1d_int32_step(&rb1d_int32_testHandler, i);
    }

    rb1d_int32_get_ordered_arr(&rb1d_int32_testHandler, rb1d_int32_orderedArr);

    rb1d_int32_heap_init(&rb1d_int32_testHandler, 10, true);

    for (int i=0;i<15;i++) {
        rb1d_int32_step(&rb1d_int32_testHandler, i);
    }

    rb1d_int32_get_ordered_arr(&rb1d_int32_testHandler, rb1d_int32_orderedArr);

    rb1d_int32_heap_delete(&rb1d_int32_testHandler);
#endif

#ifdef TEST_F32_2D
    // normal version test
    rb2d_f32_init(&rb2d_f32_testHandler, (float32_t*)rb2d_f32_arr, rb2d_f32_src, rb2d_f32_row, rb2d_f32_col, 20, 10);
    for (int i = 0; i < 15; i++) {
        // init src
        for (int j = 0;j < 20;j++) {
            rb2d_f32_testHandler.src[j] = j + i;
        }
        // arr step
        rb2d_f32_step(&rb2d_f32_testHandler);
    }

    rb2d_f32_get_ordered_row(&rb2d_f32_testHandler, 1, NULL);

    rb2d_f32_get_unordered_row(&rb2d_f32_testHandler, 0, NULL);

    rb2d_f32_get_column(&rb2d_f32_testHandler, 1, NULL);

    rb2d_f32_get_current_column(&rb2d_f32_testHandler, NULL);

    rb2d_f32_get_oldest_column(&rb2d_f32_testHandler, NULL);

    float32_t v;
    rb2d_f32_get_value(&rb2d_f32_testHandler, 0, 0, &v);
    printf("%f", v);

    // heap version test
    rb2d_f32_heap_init(&rb2d_f32_testHandler, 20, 10);
    for (int i = 0; i < 15; i++) {
        // init src
        for (int j = 0;j < 20;j++) {
            rb2d_f32_testHandler.src[j] = j + i;
        }
        // arr step
        rb2d_f32_step(&rb2d_f32_testHandler);
    }

    rb2d_f32_get_ordered_row(&rb2d_f32_testHandler, 1, NULL);

    rb2d_f32_get_unordered_row(&rb2d_f32_testHandler, 0, NULL);

    rb2d_f32_get_column(&rb2d_f32_testHandler, 1, NULL);

    rb2d_f32_get_current_column(&rb2d_f32_testHandler, NULL);

    rb2d_f32_get_oldest_column(&rb2d_f32_testHandler, NULL);

    rb2d_f32_heap_delete(&rb2d_f32_testHandler);

#endif

    return 0;
}
