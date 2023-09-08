EXEC := matrix_oop_test

SLIB := matrix_oop.a

TEST := test_matrix.cc

CC := g++
STANDART := -std=c++17
CFLAGS := -Wall -Werror -Wextra $(STANDART)
LKFLAGS := -g -fprofile-arcs -ftest-coverage
CPPCHECKFLAG := --enable=all --language=c++ -$(STANDART) --suppress=missingIncludeSystem
LDFLAGS := -lgtest
VFLAG := --leak-check=full --show-leak-kinds=all -s
TEST_FLAGS = -fprofile-arcs -ftest-coverage

OS := $(shell uname)
ifeq ($(OS), Darwin)
LEAKS := leaks --atExit -- ./$(EXEC)
endif
ifeq ($(OS), Linux)
LEAKS := valgrind $(VFLAG) ./$(EXEC)
LDFLAGS += -lpthread -lgtest_main -L/usr/lib
endif

P_LINT := ../materials/linters

CSOURCES := $(wildcard *.cc)
CHEADERS := $(wildcard *.h)
COBJ := $(CSOURCES:.cc=.o)
HOBJ := $(CHEADERS:.h=.gch)

all: $(SLIB)

style:
	-cp $(P_LINT)/.clang-format .
	clang-format -n *.cc
	clang-format -n *.h
	-cppcheck $(CPPCHECKFLAG) *.h *.cc

################## Leaks check ###################
leaks: $(EXEC)
	$(LEAKS)

############ Cleaning up unused files ############
clean:
	-@rm -rf $(EXEC)
	-@rm -rf *.o
	-@rm -rf *.gch
	-@rm -rf *.a
	-@rm -rf *.gcno
	-@rm -rf *.gcda
	-@rm -rf report
	-@rm -rf *.info
	-@rm -rf .clang-format
	-@rm -rf *.tgz
	-@rm -rf build_tests/
	-@rm -rf *.out
	-@rm -rf *.dSYM

####### Template for creating object files #######
%.o : %.cc
	$(CC) $(CFLAGS) -c $< -o $@

### Template for creating header object files ###
%.gch : %.h
	$(CC) $(CFLAGS) -c $< -o $@

##############   Create exit file   ##############
$(EXEC): 
	$(CC) $(CFLAGS) --coverage -o $(EXEC) $< *.cc $(LDFLAGS) 

##############         Tests        ##############
test: $(EXEC)
	./$(EXEC)

##############     gcov report      ##############
lcov: test
	lcov --no-external -t "$(EXEC)" -o $(EXEC).info -c -d .
	genhtml -o report $(EXEC).info

##############   matrix_oop.a   ##############
$(SLIB): $(COBJ) $(HOBJ)
	ar -rvs $(SLIB) $<
	