# cbase — a small C base library (linked list + string utilities)
#
# Usage:
#   make            Build the static library and all examples
#   make lib        Build only the static library (build/libcbase.a)
#   make examples   Build the example programs (build/examples/)
#   make tests      Build the test programs (build/tests/)
#   make test       Build and run the tests
#   make run        Build and run the first example
#   make compdb     Generate compile_commands.json (for clangd / editors)
#   make clean      Remove all build output

# --- Directories -------------------------------------------------------------
INCLUDE_DIR      := include
SRC_DIR          := src
TEST_DIR         := tests
EXAMPLE_DIR      := examples

BUILD_DIR        := build
OBJ_DIR          := $(BUILD_DIR)/obj
EXAMPLE_BIN_DIR  := $(BUILD_DIR)/examples
TEST_BIN_DIR     := $(BUILD_DIR)/tests

# --- Toolchain ---------------------------------------------------------------
CC      := cc
AR      := ar
CFLAGS  := -std=c11 -Wall -Wextra -I$(INCLUDE_DIR)
ARFLAGS := rcs

# --- Files -------------------------------------------------------------------
LIB          := $(BUILD_DIR)/libcbase.a
SRCS         := $(wildcard $(SRC_DIR)/*.c)
OBJS         := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

EXAMPLE_SRCS := $(wildcard $(EXAMPLE_DIR)/*.c)
EXAMPLE_BINS := $(patsubst $(EXAMPLE_DIR)/%.c,$(EXAMPLE_BIN_DIR)/%,$(EXAMPLE_SRCS))

TEST_SRCS    := $(wildcard $(TEST_DIR)/*.c)
TEST_BINS    := $(patsubst $(TEST_DIR)/%.c,$(TEST_BIN_DIR)/%,$(TEST_SRCS))

DB_SRCS      := $(SRCS) $(EXAMPLE_SRCS) $(TEST_SRCS)
COMPILE_DB   := compile_commands.json

# --- Default target ----------------------------------------------------------
.PHONY: all
all: lib examples $(COMPILE_DB)

# --- Static library ----------------------------------------------------------
.PHONY: lib
lib: $(LIB)

$(LIB): $(OBJS)
	@mkdir -p $(dir $@)
	$(AR) $(ARFLAGS) $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Examples ----------------------------------------------------------------
.PHONY: examples
examples: $(EXAMPLE_BINS)

$(EXAMPLE_BIN_DIR)/%: $(EXAMPLE_DIR)/%.c $(LIB)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< $(LIB) -o $@

# --- Tests -------------------------------------------------------------------
.PHONY: tests
tests: $(TEST_BINS)

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(LIB)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< $(LIB) -o $@

.PHONY: test
test: tests
	@for t in $(TEST_BINS); do echo "==> $$t"; "$$t" || exit 1; done

# --- Compilation database (for clangd and other editor tooling) --------------
# Uses absolute paths so headers resolve no matter which subfolder a file is in.
.PHONY: compdb
compdb: $(COMPILE_DB)

$(COMPILE_DB): $(DB_SRCS) Makefile
	@echo '[' > $@
	@first=1; for f in $(DB_SRCS); do \
	  if [ $$first -eq 1 ]; then first=0; else printf ',\n' >> $@; fi; \
	  printf '  {"directory": "%s", "file": "%s", "command": "%s %s -c %s"}' \
	    "$(CURDIR)" "$$f" "$(CC)" "$(CFLAGS)" "$$f" >> $@; \
	done
	@printf '\n]\n' >> $@
	@echo "Wrote $@ ($(words $(DB_SRCS)) entries)"

# --- Convenience -------------------------------------------------------------
.PHONY: run
run: examples
	@bin=$$(echo $(EXAMPLE_BINS) | awk '{print $$1}'); echo "==> $$bin"; "$$bin"

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
