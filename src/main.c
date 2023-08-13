/*
 * Copyright (c) 2023 Aiden Fox Ivey <aiden@fox-ivey.com>
 * All rights reserved.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bloom.h"

#define MAXLEN 32

int main(int argc, char *argv[]) {
  if (argc == 1 || argc > 2) {
    printf("USAGE: main [file]\n");
    return 1;
  }

  FILE *f = fopen(argv[1], "r");
  char line[MAXLEN];

  if (f != NULL) {
    BLOOM_FILTER *filter = make_bloom_filter(640, 3);

    while (fgets(line, MAXLEN, f) != NULL) {
      line[strcspn(line, "\r\n")] = 0;

      insert_bloom_filter(filter, line, (uint16_t)strlen(line));
    }

    print_bit_array_data(filter->bit_arr);

    printf("%d\n", query_bloom_filter(filter, "Toronto", 7));
    printf("%d\n", query_bloom_filter(filter, "Montreal", 8));
    printf("%d\n", query_bloom_filter(filter, "amlanta", 7));

    fclose(f);
    destroy_bloom_filter(filter);
  } else {
    printf("Unable to open file: %s.\n", argv[1]);
    return 1;
  }

  return 0;
}
