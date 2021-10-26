# SPDX-License-Identifier: MIT
CC = gcc
CFLAGS = -Wall -Wextra -Wconversion -pedantic -Werror -Iincludes -std=c99 # LDLIBS=-lstdc++
VPATH = src src/map src/lists test
LDLIBS =

# Binaries used by various commands
DEPS = gcov doxygen valgrind clang-format
# Binaries to be built
TARGETS = bst vector
# Folders containing source code
FOLDERS = ./ src/ src/map/ test/ src/lists
# List of all source code files
SRC = $(shell find src includes test -type f -name *.[ch])

# Enable debug symbols and code coverage
ifdef DEBUG
	CFLAGS += -DDEBUG -ggdb3 -fprofile-arcs -ftest-coverage
	LDLIBS += -lgcov --coverage

# Disable assert macro and optimize output
# - reason for including -g1: https://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html#:~:text=Level%201%20produces%20minimal%20information%2C%20enough%20for%20making%20backtraces%20in%20parts%20of%20the%20program%20that%20you%20don%E2%80%99t%20plan%20to%20debug.%20This%20includes%20descriptions%20of%20functions%20and%20external%20variables%2C%20and%20line%20number%20tables%2C%20but%20no%20information%20about%20local%20variables.
else ifdef PROD
	CFLAGS += -O1 -DNDEBUG -g1
endif

.PHONY: all
all: $(TARGETS)

# ================================== TESTING ===================================

.PHONY: *.report check

check: check-deps $(addsuffix .report, $(TARGETS))

bst.report: bst
	valgrind --leak-check=full ./bst
	gcov --all-blocks --branch-counts test/bst.c src/map/bintree.c

# %.report: %
# 	gcov test/$<.c
bst: test/bst.o src/map/bintree.o

vector.report: vector
	valgrind --leak-check=full ./vector
	gcov --all-blocks --branch-counts test/vector.c src/lists/vector.c

vector: test/vector.o src/lists/vector.o

# ==================================== UTIL ====================================

.PHONY: install clean check-deps lint

docs: $(SRC) Doxyfile README.md
	doxygen

install:
	apt-get install $(DEPS) -y

check-deps: check-deps.target
check-deps.target:
	@./check-deps.sh $(DEPS)
	@touch check-deps.target

lint: check-deps
	clang-format -i $(SRC)

clean:
	$(RM) -rf \
		$(addsuffix *.o, $(FOLDERS)) \
		$(addsuffix *.gcov, $(FOLDERS)) \
		$(addsuffix *.gcno, $(FOLDERS)) \
		$(TARGETS) \
		*.target
