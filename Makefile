# SPDX-License-Identifier: MIT
CC = gcc
CFLAGS = -Wall -Wextra -Wconversion -pedantic -Werror -Iincludes -std=c99 # LDLIBS=-lstdc++
VPATH = src src/map test
LDLIBS =

# Binaries used by various commands
DEPS = gcov doxygen valgrind clang-format
# Binaries to be built
TARGETS = bst vector
# Folders containing source code
FOLDERS = ./ src/ src/map/ test/ src/lists

# Enable debug symbols and code coverage
ifdef DEBUG
	CFLAGS += -DDEBUG -ggdb -fprofile-arcs -ftest-coverage
	LDLIBS += -lgcov --coverage

# Disable assert macro and optimize output
else ifdef PROD
	CFLAGS += -O1 -DNDEBUG
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

.PHONY: install clean docs check-deps lint

docs:
	doxygen

install:
	apt-get install $(DEPS) -y

check-deps: check-deps.target
check-deps.target:
	@./check-deps.sh $(DEPS)
	@touch check-deps.target

lint: check-deps
	clang-format -i \
	$(addsuffix *.c, $(FOLDERS)) \
	$(addsuffix *.h, $(FOLDERS))
clean:
	$(RM) -rf \
		$(addsuffix *.o, $(FOLDERS)) \
		$(addsuffix *.gcov, $(FOLDERS)) \
		$(addsuffix *.gcno, $(FOLDERS)) \
		$(TARGETS) \
		*.target
