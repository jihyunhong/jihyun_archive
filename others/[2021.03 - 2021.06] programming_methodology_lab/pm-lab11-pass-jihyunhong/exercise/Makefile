CC = g++
CFLAGS = -W -Wall -Og --std=c++14
CCFLAGS= ${CFLAGS}

ONE= 1/swap.cpp
TWO= 2/maximizeUtility.cpp

ONE_TARGET = swap
TWO_TARGET = maximizeUtility

ONE_OBJECTS = 1/swap.o
TWO_OBJECTS = 2/maximizeUtility.o

ONE_DEPS:= 1/test.h
TWO_DEPS:= 

all : one two

$(ONE_OBJECTS): %.o : %.cpp $(ONE_DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TWO_OBJECTS): %.o : %.cpp $(ONE_DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

one : $(ONE_OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $(ONE_TARGET) $^

two : $(TWO_OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $(TWO_TARGET) $^

clean :
	rm -rf $(ONE_OBJECTS) $(TWO_OBJECTS) $(ONE_TARGET) $(TWO_TARGET)

