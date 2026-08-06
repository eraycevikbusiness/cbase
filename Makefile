# cbase — a small C base library
#
#   make        Build build/libcbase.a plus one binary per examples/*.c
#   make test   Build and run everything in tests/
#   make clean  Delete build/
#
# Editors need no setup step: .clangd carries the include path.

# Windows names executables foo.exe. Without this the target file never
# matches what the compiler wrote, and make relinks on every run.
ifeq ($(OS),Windows_NT)
EXE := .exe
endif

CFLAGS := -std=c11 -Wall -Wextra -Iinclude

# Every src/*.c becomes a build/*.o; every examples/*.c its own program.
OBJS  := $(patsubst src/%.c,build/%.o,$(wildcard src/*.c))
DEMOS := $(patsubst examples/%.c,build/%$(EXE),$(wildcard examples/*.c))

all: $(DEMOS)

# -MMD (below) makes the compiler note which headers each .c pulled in.
# Reading those notes back here is what makes editing a header rebuild
# whatever uses it. The leading '-' means "skip if not generated yet".
-include $(OBJS:.o=.d)

# $< is the .c input, $@ is the .o output. -MMD belongs only here: the link
# step would write the same .d filenames and clobber these.
build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -MMD -c $< -o $@

build/libcbase.a: $(OBJS)
	ar rcs $@ $(OBJS)

# $^ is every prerequisite: the example source plus the library.
build/%$(EXE): examples/%.c build/libcbase.a
	$(CC) $(CFLAGS) $^ -o $@

# Each test file has its own main(), so they are built one at a time.
test: build/libcbase.a
	@for t in tests/*.c; do \
	  $(CC) $(CFLAGS) $$t build/libcbase.a -o build/t$(EXE) && ./build/t$(EXE) || exit 1; \
	done

clean:
	rm -rf build

.PHONY: all test clean
