#include <stdio.h>
#include <stdlib.h>
#include "value.h"
#include "ops.h"

int main() {
  Value_t* val1 = init_value();
  Value_t* val2 = init_value();
  Value_t* val3 = init_value();

  val1->data = 2.0;
  val2->data = 1.0;
  val3->data = -3.0;

  val3 = mul(val1, val2);
  Value_t *val4 = relu(val3);

  val4->grad = 1.0;
  val4->_backward(val4);
  val3->_backward(val3);

  printf("val1.grad %.2f\n", val1->grad);
  printf("val2.grad %.2f\n", val2->grad);
  printf("val3.grad %.2f\n", val3->grad);
  printf("val4.grad %.2f\n", val4->grad);

  free_value(val1);
  free_value(val2);
  free_value(val3);
  free_value(val4);
  return 0;
}