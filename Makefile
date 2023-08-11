all:
	mkdir -p build
	gcc src/main.c -o build/main

.PHONY: clean
clean:
	rm -rf build
