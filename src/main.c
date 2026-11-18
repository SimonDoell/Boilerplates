#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "types.h"
#include "debug.h"
#include "result.h"

typedef bool(*BiggerThen)(void const* lhs, void const* rhs);

static MUST_USE Result heapify(void* elements, u32 element_size, u32 element_count, BiggerThen bigger_then, u32 index) {
    if (!c_assert(elements != NULL) || !c_assert(bigger_then != NULL))
        return RESULT_ERROR_NULL_POINTER_ARGUMENT;

    if (!c_assert(element_size > 0) || !c_assert(element_count > 0))
        return RESULT_ERROR_INVALID_ARGUMENT;

    u32 largest = index;
    u32 left    = index * 2 + 1;
    u32 right   = index * 2 + 2;

    void* index_ptr   = &((u8*)elements)[element_size * index];
    void* largest_ptr = &((u8*)elements)[element_size * largest];
    void* left_ptr    = &((u8*)elements)[element_size * left];
    void* right_ptr   = &((u8*)elements)[element_size * right];

    if (left < element_count && bigger_then(left_ptr, largest_ptr))
        largest = left;

    largest_ptr = &((u8*)elements)[element_size * largest];

    if (right < element_count && bigger_then(right_ptr, &((u8*)elements)[element_size * largest]))
        largest = right;

    if (largest != index) {
        largest_ptr = &((u8*)elements)[element_size * largest];
        
        u8 temp[element_size];

        memcpy(temp, index_ptr,  element_size);
        memcpy(index_ptr, largest_ptr, element_size);
        memcpy(largest_ptr, temp, element_size);
        
        if (!c_assert(heapify(elements, element_size, element_count, bigger_then, largest) == RESULT_OK)) {
            return RESULT_ERROR_FAILED_FUNCTION_CALL;
        }
    }

    return RESULT_OK;
}

static MUST_USE Result build_heap(void* elements, u32 element_size, u32 element_count, BiggerThen bigger_then) {
    u32 start_index = (element_count - 1) / 2;

    for (u32 i = start_index + 1; i-- > 0;) {
        if (!c_assert(heapify(elements, element_size, element_count, bigger_then, i) == RESULT_OK)) {
            return RESULT_ERROR_FAILED_FUNCTION_CALL;
        }
    }

    return RESULT_OK;
}

static MUST_USE Result heapsort(void* elements, u32 element_size, u32 element_count, BiggerThen bigger_then) {
    if (!c_assert(elements != NULL) || !c_assert(bigger_then != NULL))
        return RESULT_ERROR_NULL_POINTER_ARGUMENT;

    if (!c_assert(element_size > 0) || !c_assert(element_count > 0))
        return RESULT_ERROR_INVALID_ARGUMENT;

    if (!c_assert(build_heap(elements, element_size, element_count, bigger_then) == RESULT_OK)) {
        return RESULT_ERROR_FAILED_FUNCTION_CALL;
    }

    u8 temp[element_size];
    void* first = elements;

    for (u32 index = element_count - 1; index > 0; --index) {
        void* last = &((u8*)elements)[(index) * element_size];

        // Swap
        memcpy(temp, last,  element_size);
        memcpy(last, first, element_size);
        memcpy(first, temp, element_size);
        
        element_count--;

        if (!c_assert(heapify(elements, element_size, element_count, bigger_then, 0) == RESULT_OK))
            return RESULT_ERROR_FAILED_FUNCTION_CALL;
    }

    return RESULT_OK;
}

#ifndef countof
#define countof(arr) (sizeof(arr)/sizeof(arr[0]))
#endif

static bool i32_compare(void const* lhs, void const* rhs) {
    i32 const* l = lhs;
    i32 const* r = rhs;
    return *l > *r;
}

int main(void) {
    u32 count = 32000000;
    
    i32* values = malloc(count * sizeof(i32));

    if (!values) {return 1;}

    for (u32 i = 0; i < count; ++i)
        values[i] = rand() % 100;

    c_assert(heapsort(values, sizeof(i32), count, i32_compare) == RESULT_OK);

    printf("Done!\n");
    
    return 0;
}