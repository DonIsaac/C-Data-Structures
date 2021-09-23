CC = gcc
CFLAGS = -Wall -Wextra -Wconversion -pedantic -Iincludes -std=c99 # LDLIBS=-lstdc++
VPATH = src src/map test
LDLIBS = -lgcov --coverage

TARGETS = bst
FOLDERS = ./ src/ src/map/ test/

ifdef DEBUG
	CFLAGS += -DDEBUG -ggdb -fprofile-arcs -ftest-coverage
endif

.PHONY: all
all: $(TARGETS)

# ================================== TESTING ===================================

.PHONY: *.report

# bst.report: test/bst.o bintree.o
bst.report: bst
	./bst
	gcov -a -c -f test/bst.c src/map/bintree.o
# %.report: %
# 	gcov test/$<.c
bst: test/bst.o src/map/bintree.o

# %.tst: test/%.o

# ==================================== UTIL ====================================

.PHONY: install clean

install:
	apt-get install gcov doxygen -y

clean:
	$(RM) -rf \
		$(addsuffix *.o, $(FOLDERS)) \
		$(addsuffix *.gcov, $(FOLDERS)) \
		$(addsuffix *.gcno, $(FOLDERS)) \
		$(TARGETS)
