# cbase — a small C base library
#
#   make        Build build/libcbase.a and the example (build/main)
#   make test   Build and run everything in tests/
#   make clean  Delete build/
#
# Editors need no setup step: .clangd carries the include path.

# Windows names executables foo.exe. Without this the target file never
# matches what the compiler wrote, and make relinks on every run.
ifeq ($(OS),Windows_NT)
EXE := .exe
endif

# -MMD makes the compiler record which headers each .c pulled in.
CFLAGS := -std=c11 -Wall -Wextra -Iinclude -MMD

# Every src/*.c gets a matching build/*.o. $(CC) defaults to cc.
OBJS := $(patsubst src/%.c,build/%.o,$(wildcard src/*.c))

all: build/main$(EXE)

# Read those recorded header lists, so editing a header rebuilds what uses
# it. The leading '-' means "skip silently if the files do not exist yet".
-include $(OBJS:.o=.d)

# $< is the .c input, $@ is the .o output.
build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

build/libcbase.a: $(OBJS)
	ar rcs $@ $(OBJS)

# $^ is every prerequisite: the example source plus the library.
build/main$(EXE): examples/main.c build/libcbase.a
	$(CC) $(CFLAGS) $^ -o $@

# Each test file has its own main(), so they are built one at a time.
test: build/libcbase.a
	@for t in tests/*.c; do \
	  $(CC) $(CFLAGS) $$t build/libcbase.a -o build/t$(EXE) && ./build/t$(EXE) || exit 1; \
	done

clean:
	rm -rf build

.PHONY: all test clean
