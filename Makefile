CC      := clang
CFLAGS  := -Iinclude -std=c17 -Wall -Wextra -g -fsanitize=address,undefined
LDFLAGS := -fsanitize=address,undefined

SRC   := $(wildcard src/*.c)
TESTS := $(wildcard tests/*.c)
BUILD := build

.PHONY: all test clean

all: $(BUILD)/test_runner

$(BUILD)/test_runner: $(SRC) $(TESTS) | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILD):
	mkdir -p $(BUILD)

test: $(BUILD)/test_runner
	./$(BUILD)/test_runner

clean:
	rm -rf $(BUILD)
