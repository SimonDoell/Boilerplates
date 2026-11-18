#ifndef RESULT_H
#define RESULT_H

typedef enum {
    RESULT_OK                          = 0,
    RESULT_ERROR_INVALID_ARGUMENT      = 1,
    RESULT_ERROR_INDEX_OUT_OR_RANGE    = 2,
} Result;

#endif