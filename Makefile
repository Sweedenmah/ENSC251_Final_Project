#simplifying makefile and ensuring latest c++ standard supported by gcc 4.8.5
CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -Wextra -Wconversion -Wfloat-equal -Wold-style-cast -Wshadow -Wuseless-cast -pedantic
EXTRAFLAGS = -Wlogical-op -Wduplicated-branches -Wduplicated-cond -Wnull-dereference # not supported on gcc 4.8.5
CC = $(CXX) $(CXXFLAGS)

#compile and link the application
all: main

#run the application
run: main
	./main

#mainly for use by automated testing
testruncheck: unit_testcheck
	./unit_testcheck

testrun: test
	./test

#run default tests
test: unit_test.o student.o international.o domestic.o helpers.o toefl.o templates.o ncmenu.o
	$(CC) -o test unit_test.o student.o international.o domestic.o helpers.o toefl.o templates.o ncmenu.o -lmenu -lncurses

#test with extra error flags
unit_testcheck: unit_test.ocheck student.ocheck international.ocheck domestic.ocheck helpers.ocheck toefl.ocheck templates.ocheck ncmenu.ocheck
	$(CC) $(EXTRAFLAGS) -o unit_testcheck unit_test.o student.o international.o domestic.o helpers.o toefl.o templates.o ncmenu.o -lmenu -lncurses

#simple alias
check: maincheck

#extra error flags
maincheck: main.ocheck student.ocheck international.ocheck domestic.ocheck helpers.ocheck toefl.ocheck templates.ocheck list.ocheck ncmenu.ocheck
	$(CC) $(EXTRAFLAGS) -o main main.o student.o international.o domestic.o helpers.o toefl.o templates.o list.o ncmenu.o -lmenu -lncurses

#link main.o and student.o to executable main
main: main.o student.o international.o domestic.o helpers.o toefl.o templates.o list.o ncmenu.o
	$(CC) -o main main.o student.o international.o domestic.o helpers.o toefl.o templates.o list.o ncmenu.o -lmenu -lncurses

#all object files
%.o: %.cpp
	$(CC) -c -o $@ $<

#with extra error flags
%.ocheck: %.cpp
	$(CC) $(EXTRAFLAGS) -c $<

#remove built files
clean:
	rm -rf unit_test test unit_testcheck main *~ *.o
