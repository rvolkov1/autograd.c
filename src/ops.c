#include <stdlib.h>
#include "ops.h"

// ADDITION
void add_backward(Value_t* val) {
  if (val->_prev[0]) {
    val->_prev[0]->grad += 1.0 * val->grad;
  }

  if (val->_prev[1]) {
    val->_prev[1]->grad += 1.0 * val->grad;
  }
}

Value_t* add(Value_t* a, Value_t* b) {
  Value_t *out = init_value();
  out->data = a->data + b->data;
  out->op = Add;
  out->_prev[0] = a;
  out->_prev[1] = b;
  out->_backward = add_backward;
  return out;
}

// MULTIPLICATION
void mul_backward(Value_t* val) {
  if (val->_prev[0] && val->_prev[1]) {
    val->_prev[0]->grad += val->_prev[1]->data * val->grad;
    val->_prev[1]->grad += val->_prev[0]->data * val->grad;
  }
}

Value_t* mul(Value_t* a, Value_t* b) {
  printf("beginning of mul\n");
  Value_t *out = init_value();
  out->data = a->data * b->data;
  out->op = Mul;
  out->_prev[0] = a;
  out->_prev[1] = b;
  out->_backward = mul_backward;
  printf("end of mul\n");
  return out;
}