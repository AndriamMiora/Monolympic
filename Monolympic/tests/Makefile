CC=g++
CCFLAGS= -Wall -std=c++11 -g
SRC= $(wildcard ../*.cc)
OBJ= $(SRC:.cc=.o)
TST= $(wildcard *.cc)
OBJ_TEST = $(filter-out ../main.o, $(OBJ)) $(TST:.cc=.o)

testcase.out : $(OBJ_TEST) 
	$(CC) $(CCFLAGS)  -o $@ $^

%.o: %.cc
	$(CC) $(CCFLAGS) -I../ -o $@ -c $<

test: testcase.out
	./testcase.out
.depend:
	g++ $(CCFLAGS) -MM $(SRC) > .depends
-include .depends

clean :
	rm -f $(OBJ_TEST) testcase.out
