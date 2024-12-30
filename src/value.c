#include "value.h"

Value_t* init_value() {
  Value_t* out = (Value_t*)malloc(sizeof(Value_t));
  out->data = 1.0;
  out->grad = 0.0;
  return out;
}

void free_value(Value_t* a) {
  free(a);
}