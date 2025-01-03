#ifndef OPS_H
#define OPS_H

#include <stdlib.h>
#include <stdio.h>
#include "value.h"

void add_backward(Value_t* val);
Value_t* addf(Value_t* a, float b);
Value_t* add(Value_t* a, Value_t* b);

void mul_backward(Value_t* val);
Value_t* mulf(Value_t* a, float b);
Value_t* mul(Value_t* a, Value_t* b);

void relu_backward(Value_t* val);
Value_t* relu(Value_t* a);

#endif // OPS_H