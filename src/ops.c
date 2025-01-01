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

Value_t* addf(Value_t* a, float b) {
  Value_t* val_b = init_value();
  val_b->data = b;
  return add(a, val_b);
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

Value_t* mulf(Value_t* a, float b) {
  Value_t* val_b = init_value();
  val_b->data = b;
  return mul(a, val_b);
}

Value_t* mul(Value_t* a, Value_t* b) {
  Value_t *out = init_value();
  out->data = a->data * b->data;
  out->op = Mul;
  out->_prev[0] = a;
  out->_prev[1] = b;
  out->_backward = mul_backward;
  return out;
}

// ReLU
void relu_backward(Value_t* val) {
  if (val->_prev[0]) {
    float grad = 0.0;
    if (val->_prev[0]->data > 0) {
      grad = 1.0;
    }
    val->_prev[0]->grad += grad * val->grad;
  }
}


Value_t* relu(Value_t* a) {
  Value_t *out = init_value();
  if (out->data <= 0) {
    out->data = 0;
  }
  out->op = ReLU;
  out->_prev[0] = a;
  out->_backward = relu_backward;
  return out;
}