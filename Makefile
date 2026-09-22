# Build script for the technology park manager.
#
#   make            -> builds ./bin/parque-tecnologico
#   make run        -> builds and runs the program
#   make test       -> builds and runs the unit tests
#   make memcheck   -> runs the unit tests under Valgrind (Linux only)
#   make docs       -> generates the Doxygen documentation in docs/html
#   make clean      -> removes everything that was generated

CC      ?= gcc
CFLAGS  ?= -std=c11 -Wall -Wextra -pedantic -O2
CPPFLAGS = -Iinclude

BIN_DIR = bin
OBJ_DIR = obj
TARGET  = $(BIN_DIR)/parque-tecnologico
TEST_TARGET = $(BIN_DIR)/tests

SOURCES  = $(wildcard src/*.c)
OBJECTS  = $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
# Everything except main.o is shared with the test executable.
LIB_OBJECTS = $(filter-out $(OBJ_DIR)/main.o,$(OBJECTS))

.PHONY: all run test memcheck docs clean

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(TEST_TARGET): tests/test_core.c $(LIB_OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -MP -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

memcheck: $(TEST_TARGET)
	valgrind --leak-check=full --error-exitcode=1 ./$(TEST_TARGET)

docs:
	doxygen docs/Doxyfile

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) docs/html

-include $(OBJECTS:.o=.d)
