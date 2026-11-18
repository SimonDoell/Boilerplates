#ifndef RESULT_H
#define RESULT_H

typedef enum {
    RESULT_OK                          = 0,
    RESULT_ERROR_INVALID_ARGUMENT      = 1,
    RESULT_ERROR_INDEX_OUT_OR_RANGE    = 2,
    RESULT_ERROR_DIVISION_BY_ZERO      = 3,
} Result;

#if defined(__GNUC__) || defined(__clang__)
    #define MUST_USE __attribute__((warn_unused_result))
#else
    #define MUST_USE
#endif

#endif