/*
 * Copyright (c) 2023 Aiden Fox Ivey <aiden@fox-ivey.com>
 * All rights reserved.
 */

#include "bloom.h"
#include "hash.h"

BIT_ARRAY *make_bit_array(int64_t num_bits) {
  int64_t nearest_64_multiple = ((num_bits + 63) >> 6) << 6;
  int64_t num_words = nearest_64_multiple >> 6;
  int64_t *words = malloc(sizeof(int64_t) * num_words);

  BIT_ARRAY *arr = malloc(sizeof(BIT_ARRAY));
  arr->words = words;
  arr->num_bits = num_bits;
  arr->num_words = num_words;
  arr->left_over_bits = nearest_64_multiple - num_bits;

  return arr;
}

void destroy_bit_array(BIT_ARRAY *arr) {
  if (arr == NULL) {
    assert(false && "bit array is already deallocated!");
  }

  free(arr->words);
  free(arr);
}

void print_bit_array_metadata(BIT_ARRAY *arr) {
  if (arr == NULL) {
    return;
  }
  printf("BIT_ARRAY {\n BITS:\t\t%lld\n WORDS:\t\t%lld\n LEFT OVER:\t%lld\n}\n",
         arr->num_bits, arr->num_words, arr->left_over_bits);
}

char *int64_to_string(int64_t n) {
  char *buffer = malloc(sizeof(char) * 65);
  buffer[64] = '\0';

  for (int i = 0; i < 64; i++) {
    if (n & 1) {
      buffer[63 - i] = '1';
    } else {
      buffer[63 - i] = '0';
    }

    n = n >> 1;
  }

  return buffer;
}

void print_bit_array_data(BIT_ARRAY *arr) {
  if (arr == NULL) {
    assert(false && "bit array not allocated!");
  }

  for (int i = (arr->num_words - 1); i >= 0; i--) {
    printf("%s\n", int64_to_string(arr->words[i]));
  }
}

int set_bit(BIT_ARRAY *arr, uint64_t idx) {
  if (idx > arr->num_bits) {
    return -1;
  }

  int word_idx = idx / 64;
  int bit_idx = idx % 64;

  arr->words[word_idx] ^= (1 << bit_idx);

  return 0;
}

int query_bit(BIT_ARRAY *arr, uint64_t idx) {
  if (idx > arr->num_bits) {
    return -1;
  }

  int word_idx = idx / 64;
  int bit_idx = idx % 64;

  if (arr->words[word_idx] & (1 << bit_idx)) {
    return 1;
  } else {
    return 0;
  }
}

BLOOM_FILTER *make_bloom_filter(uint64_t num_bits, uint8_t num_hashes) {
  BIT_ARRAY *arr = make_bit_array(num_bits);

  BLOOM_FILTER *filter = malloc(sizeof(BLOOM_FILTER));

  filter->hashes = num_hashes;
  filter->bit_arr = arr;

  return filter;
}

void destroy_bloom_filter(BLOOM_FILTER *filter) {
  destroy_bit_array(filter->bit_arr);
  free(filter);
}

void insert_bloom_filter(BLOOM_FILTER *filter, const char *str,
                         uint16_t length) {
  for (int i = 1; i <= filter->hashes; i++) {
    uint64_t h = hash(i, str, length);
    uint64_t idx = h % filter->bit_arr->num_bits;

    set_bit(filter->bit_arr, idx);
  }
}

int query_bloom_filter(BLOOM_FILTER *filter, const char *str, uint16_t length) {
  for (int i = 1; i <= filter->hashes; i++) {
    uint64_t h = hash(i, str, length);
    uint64_t idx = h % filter->bit_arr->num_bits;

    int query = query_bit(filter->bit_arr, idx);

    if (!query) {
      return 1;
    }
  }

  return 0;
}

// hash functions are originally from / inspired by:
// http://www.partow.net/programming/hashfunctions/
int64_t hash(int function, char *str, int length) {
  switch (function) {
  case 1:
    return RSHash(str, length);
  case 2:
    return JSHash(str, length);
  case 3:
    return PJWHash(str, length);
  case 4:
    return ELFHash(str, length);
  case 5:
    return BKDRHash(str, length);
  case 6:
    return SDBMHash(str, length);
  case 7:
    return DJBHash(str, length);
  case 8:
    return APHash(str, length);
  default:
    return 0;
  }
}