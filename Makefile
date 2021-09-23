CC = gcc
CFLAGS = -Wall -Wextra -Wconversion -pedantic -Iincludes -std=c99 # LDLIBS=-lstdc++
VPATH = src src/map test

ifdef DEBUG
	CFLAGS += -DDEBUG -ggdb
endif

.PHONY: all
all: bst

bst: test/bst.o bintree.o

# %.tst: test/%.o
