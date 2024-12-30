#include <stdio.h>
#include <stdlib.h>

enum OP{
  Add, Mul
};

typedef struct Value {
  float data;
  float grad;
  struct Value* _prev[2];
  enum OP op;
  void (*_backward)(struct Value*);
} Value_t;

Value_t* init_value() {
  Value_t* out = (Value_t*)malloc(sizeof(Value_t));
  out->data = 1.0;
  out->grad = 0.0;
  return out;
}

void free_value(Value_t* a) {
  free(a);
}

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

int main() {
  Value_t* val1 = init_value();
  Value_t* val2 = init_value();

  val1->data = 2.0;
  val2->data = 1.0;

  Value_t *val3 = add(val1, val2);

  printf("val3.data %.2f\n", val3->data);
  printf("val3.op: %u\n", val3->op);
  printf("val3.prev.data: %f\n", val3->_prev[1]->data);

  //val3->grad = 1.0;
  //val3->_backward(val3);

  printf("val3.grad %.2f\n", val3->grad);
  printf("val1.grad %.2f\n", val1->grad);
  printf("val2.grad %.2f\n", val2->grad);

  free_value(val1);
  free_value(val2);
  free_value(val3);
  return 0;
}