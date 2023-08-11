#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define UNIMPL assert(false && "unimplemented")

typedef struct {
	int64_t* words;
	int64_t num_bits;
	int64_t num_words;
	int64_t left_over_bits;
} BIT_ARRAY;

BIT_ARRAY* make_bit_array(int64_t num_bits) {
	int64_t	nearest_64_multiple = ((num_bits+63) >> 6) << 6;
	int64_t num_words = nearest_64_multiple / 64;
	int64_t* words = malloc(sizeof(int64_t) * num_words);

	BIT_ARRAY* arr = malloc(sizeof(BIT_ARRAY));
	arr->words = words;
	arr->num_bits = num_bits;
	arr->num_words = num_words;
	arr->left_over_bits = nearest_64_multiple - num_bits;

	return arr;
}

void destroy_bit_array(BIT_ARRAY* arr) {
	if (arr == NULL) {
		assert(false && "bit array is already deallocated!");
	}

	free(arr->words);
	free(arr);
}

void show_bit_arr_metadata(BIT_ARRAY* arr) {
	if (arr == NULL) {
		assert(false && "bit array not allocated!");
	}
	printf(
		"BIT_ARRAY {\n BITS:\t\t%lld\n WORDS:\t\t%lld\n LEFT OVER:\t%lld\n}\n", 
		arr->num_bits,
		arr->num_words,
		arr->left_over_bits
	);
}

char* int64_to_string(int64_t n) {
	char* buffer = malloc(sizeof(char) * 65);
	buffer[64] = '\0';

	for (int i = 0; i < 64; i++) {
		if (n & 1) {
			buffer[63-i] = '1';
		} else {
			buffer[63-i] = '0';
		}

		n = n >> 1;
	}

	return buffer;
}

void show_bit_arr_data(BIT_ARRAY* arr) {
	if (arr == NULL) {
		assert(false && "bit array not allocated!");
	}

	for (int i = (arr->num_words - 1); i >= 0; i--) {
		printf("%s\n", int64_to_string(arr->words[i]));
	}
}


// returns 0 on correct usage and 1 on out of bounds
int set_bit(int64_t idx, BIT_ARRAY* arr) {
	if (idx > arr->num_bits) {
		return 1;
	}

	int word_idx = idx / 64;
	int bit_idx = idx % 64;

	arr->words[word_idx] ^= (1 << bit_idx);

	return 0;
}

void unset_bit(int64_t idx) {
	UNIMPL;
}

// hash functions are originally from / inspired by:
// http://www.partow.net/programming/hashfunctions/
int64_t hash1() {UNIMPL;}
int64_t hash2() {UNIMPL;}
int64_t hash3() {UNIMPL;}
int64_t hash4() {UNIMPL;}
int64_t hash5() {UNIMPL;}
int64_t hash6() {UNIMPL;}
int64_t hash7() {UNIMPL;}
int64_t hash8() {UNIMPL;}

int main(void) {
	BIT_ARRAY* a = make_bit_array(129);
	show_bit_arr_metadata(a);
	set_bit(129, a);
	show_bit_arr_data(a);
	destroy_bit_array(a);
	return 0;
}

