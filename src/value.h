#ifndef VALUE_H
#define VALUE_H

#include <stdlib.h>

typedef enum {
    Add,
    Mul
} OP;

typedef struct Value {
    float data;
    float grad;
    struct Value* _prev[2];
    OP op;
    void (*_backward)(struct Value*);
} Value_t;

Value_t* init_value(void);
void free_value(Value_t* a);

#endif // VALUE_H