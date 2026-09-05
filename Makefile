CC = gcc
CFLAGS = -Wall -Wextra -D_GNU_SOURCE -std=c11 -g -Isrc/frontend -Isrc/midend -Isrc/backend -Isrc/toolchain
SRCDIR = src
OBJS = src/main.o src/frontend/lexer.o src/frontend/parser.o src/frontend/ast.o src/midend/type_inference.o src/midend/ssa.o src/backend/c_codegen.o src/backend/compiler.o src/toolchain/diagnostic.o src/toolchain/build.o
TARGET = superc

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

test: $(TARGET)
	./test/run_tests.sh

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
