CC = gcc
CFLAGS = -Wall -Wextra -Wconversion -pedantic -Iincludes -std=c99 # LDLIBS=-lstdc++
VPATH = src src/map test
LDLIBS = -lgcov --coverage

TARGETS = bst
FOLDERS = ./ src/ src/map/ test/

ifdef DEBUG
	CFLAGS += -DDEBUG -ggdb -fprofile-arcs -ftest-coverage
else ifdef PROD
	CFLAGS += -O1 -DNDEBUG
endif

.PHONY: all
all: $(TARGETS)

# ================================== TESTING ===================================

.PHONY: *.report check

check: bst.report

bst.report: bst
	valgrind --leak-check=full ./bst
	gcov --all-blocks --branch-counts test/bst.c src/map/bintree.c

# %.report: %
# 	gcov test/$<.c
bst: test/bst.o src/map/bintree.o

# %.tst: test/%.o

# ==================================== UTIL ====================================

.PHONY: install clean docs

docs:
	doxygen

install:
	apt-get install gcov doxygen -y

clean:
	$(RM) -rf \
		$(addsuffix *.o, $(FOLDERS)) \
		$(addsuffix *.gcov, $(FOLDERS)) \
		$(addsuffix *.gcno, $(FOLDERS)) \
		$(TARGETS)
