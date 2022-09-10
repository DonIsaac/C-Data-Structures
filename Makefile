# SPDX-License-Identifier: MIT
# C/C++ compilers
CC = gcc
CPP = g++

# =============================== COMPILER FLAGS ===============================

# Linux
LINUX_CFLAGS = -Wall -Wextra -Wconversion -pedantic -Werror -Iincludes -std=c99 # LDLIBS=-lstdc++
LINUX_CXXFLAGS = -Wall -Wextra -Wconversion -pedantic -Werror -Iincludes -std=c++17 # LDLIBS=-lstdc++
LINUX_PRODFLAGS = -02 -DNDEBUG
LINUX_DEBUGFLAGS = -DDEBUG -ggdb -fprofile-arcs -ftest-coverage
LINUX_DEBUG_LDLIBS = -lgcov --coverage

# MacOS
MACOS_CFLAGS = -Wall -Wextra -Wconversion -pedantic -Werror -Iincludes -std=c99
MACOS_CXXFLAGS = -Wall -Wextra -Wconversion -pedantic -Werror -Iincludes -std=c++17
MACOS_PRODFLAGS = -02 -DNDEBUG
MACOS_DEBUGFLAGS = -DDEBUG -g 
MACOS_DEBUG_LDLIBS =

# Windows
# todo

# ==============================================================================

# Virtual paths for make to check, prevents verbose paths to src files
VPATH = src src/map test
# Libraries to link in production
LDLIBS =

# Binaries used by various commands
DEPS = gcov doxygen valgrind clang-format
# Binaries to be built
TARGETS = bst vector quadtree
# Folders containing source code
FOLDERS = ./ src/ src/map/ test/ src/lists

# ================================ BUILD FLAGS =================================

# Add platform-specific flags,
ifeq ($(OS), Windows_NT)
# NOTE: Windows is not supported yet
   CFLAGS += -D WIN32
	ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
	CFLAGS += -D AMD64
	else
		ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
           CFLAGS += -D AMD64
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),x86)
           CFLAGS += -D IA32
		endif
    endif

else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CFLAGS += $(LINUX_CFLAGS)
		CXXFLAGS += $(LINUX_CXXFLAGS)
		PRODFLAGS += $(LINUX_PRODFLAGS)
		DEBUGFLAGS += $(LINUX_DEBUGFLAGS)
		DEBUG_LDLIBS += $(LINUX_DEBUG_LDLIBS)
	else
		CFLAGS += $(MACOS_CFLAGS)
		CXXFLAGS += $(MACOS_CXXFLAGS)
		PRODFLAGS += $(MACOS_PRODFLAGS)
		DEBUGFLAGS += $(MACOS_DEBUGFLAGS)
		DEBUG_LDFLAGS += $(MACOS_DEBUG_LDFLAGS)

	endif
endif

# Enable debug symbols and code coverage
ifdef DEBUG
	CFLAGS += $(DEBUGFLAGS)
	CXXFLAGS += $(DEBUGFLAGS)
	LDLIBS += $(DEBUG_LDLIBS)

# Disable assert macro and optimize output
else ifdef PROD
	CFLAGS += $(PRODFLAGS)
	CXXFLAGS += $(PRODFLAGS)
endif

# ================================== TARGETS ===================================

.PHONY: all
all: $(TARGETS)

bst: test/bst.o src/map/bintree.o
vector: test/vector.o src/lists/vector.o
quadtree: test/quadtree.o src/map/quadtree.o src/lib/geometry.o src/lib/epsilon.o

# ================================== TESTING ===================================

.PHONY: *.report check test

test: $(TARGETS)
	@echo "Running tests..."
	@for test in $(TARGETS); do \
		echo "\n======================== Running $$test tests ========================\n"; \
		./$$test; \
	done

check: check-deps $(addsuffix .report, $(TARGETS))

bst.report: bst
	valgrind --leak-check=full ./bst
	gcov --all-blocks --branch-counts test/bst.c src/map/bintree.c

# %.report: %
# 	gcov test/$<.c

vector.report: vector
	valgrind --leak-check=full ./vector
	gcov --all-blocks --branch-counts test/vector.c src/lists/vector.c


# ==================================== UTIL ====================================

.PHONY: foo
foo:
	echo ${OS}
	exit

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
