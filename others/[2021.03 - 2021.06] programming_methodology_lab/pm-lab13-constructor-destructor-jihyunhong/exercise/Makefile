CC = g++
CCFLAGS= -Og -std=c++17

ONE_SOURCES = 1/queue.cpp 1/stack.cpp 1/main.cpp
TWO_SOURCES = 2/msg.cpp

ONE_OBJS = 1/queue.o 1/stack.o 1/main.o
TWO_OBJS = 2/msg.o

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
