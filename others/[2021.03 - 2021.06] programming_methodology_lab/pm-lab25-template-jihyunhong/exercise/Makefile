CC = g++
CCFLAGS= -Og -std=c++17
ONE_SOURCES = 1/main.cpp 1/arrayT.cpp
TWO_SOURCES = 2/main.cpp
ONE_OBJS = 1/main.o 1/arrayT.o
TWO_OBJS = 2/main.o
ONE_TARGET = one
TWO_TARGET = two

all : $(ONE_TARGET) $(TWO_TARGET)

$(ONE_TARGET) : $(ONE_OBJS)
	$(CC) $(CCFLAGS) -o $@ $^

$(ONE_OBJS) : %.o : %.cpp

$(TWO_TARGET) : $(TWO_OBJS)
	$(CC) $(CCFLAGS) -o $@ $^

$(TWO_OBJS) : %.o : %.cpp

clean : 
	rm -f $(ONE_TARGET) $(TWO_TARGET) $(ONE_OBJS) $(TWO_OBJS)