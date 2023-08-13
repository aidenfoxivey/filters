INCLUDE_DIR = ./include
SOURCE_DIR = ./src
BUILD_DIR = ./build

CFLAGS = -I$(INCLUDE_DIR) -g3 -Wall -Wextra -Wconversion -Wdouble-promotion \
     -Wno-unused-parameter -Wno-unused-function -Wno-sign-conversion \
     -fsanitize=undefined -fsanitize-trap

FAST_CFLAGS = -I$(INCLUDE_DIR) -O3

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

main: $(OBJS)
	mkdir -p build
	gcc $(OBJS) -o $(BUILD_DIR)/main

%.o: %.c
	gcc -c $< -o $@ $(CFLAGS)

.PHONY: format
format:
	clang-format --style=LLVM -i $(SOURCE_DIR)/*.c $(INCLUDE_DIR)/*.h

.PHONY: clean
clean:
	rm -rf build
