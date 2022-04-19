#include <stdio.h>

typedef enum {
    Pending,
    Success,
    IterationsExceeded,
    Overflow,
    DivisionByZero
}Status;

typedef struct {
    double x0;
    double (*g)(double);
    enum Status status;
    double result;
}RootStruct;

