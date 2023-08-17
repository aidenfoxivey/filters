#include "bloom.h"

typedef struct xor_filter_t {
  BIT_ARRAY bit;
} XOR_FILTER;