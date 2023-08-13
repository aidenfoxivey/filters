/*
 * Copyright (c) 2023 Aiden Fox Ivey <aiden@fox-ivey.com>
 * All rights reserved.
 */

#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define UNIMPL assert(false && "unimplemented")

typedef struct {
  int64_t *words;
  int64_t num_bits;
  int64_t num_words;
  int64_t left_over_bits;
} BIT_ARRAY;

BIT_ARRAY *make_bit_array(int64_t num_bits);
void destroy_bit_array(BIT_ARRAY *arr);
void print_bit_array_metadata(BIT_ARRAY *arr);
char *int64_to_string(int64_t n);
void print_bit_array_data(BIT_ARRAY *arr);
int set_bit(BIT_ARRAY *arr, uint64_t idx);
int query_bit(BIT_ARRAY *arr, uint64_t idx);

/* FUTURE ADDITIONS */
/* ------------------------------------ */
void invert(BIT_ARRAY *arr);
uint64_t hamming_weight(BIT_ARRAY *arr);
BIT_ARRAY *set_difference(BIT_ARRAY *first, BIT_ARRAY *second);
uint64_t find_first_one(BIT_ARRAY *arr);
void run_length_encode(BIT_ARRAY *arr);
/* ------------------------------------ */

typedef struct {
  uint8_t hashes;
  BIT_ARRAY *bit_arr;
} BLOOM_FILTER;

BLOOM_FILTER *make_bloom_filter(uint64_t num_bits, uint8_t num_hashes);
void destroy_bloom_filter(BLOOM_FILTER *filter);
void insert_bloom_filter(BLOOM_FILTER *filter, const char *str,
                         uint16_t length);
int query_bloom_filter(BLOOM_FILTER *filter, const char *str, uint16_t length);

int64_t hash(int function, char *str, int length);
