# Specify source and build directories
SRCDIR := src
BUILDDIR := build
INCLDIR := include

# Get list of all C source files in source directory
SOURCES := $(wildcard $(SRCDIR)/*.c) 

# Generate object file names from sources
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

# Compiler and flags
CC := clang
CFLAGS := -c -Wall -I$(INCLDIR)

TARGET := bloom

# Target to build all object files
.PHONY: all
all: $(TARGET)
	
$(TARGET): $(OBJECTS) | $(BUILDDIR)
	$(CC) $(OBJECTS) -o $(BUILDDIR)/$(TARGET)

# Rule to compile C source files into object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ $<

# Rule to create build directory
$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

# Rule to clean up build directory 
.PHONY: clean
clean:
	@rm -rf $(BUILDDIR)/*

