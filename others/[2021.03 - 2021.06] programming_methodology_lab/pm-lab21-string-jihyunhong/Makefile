CC = g++
CCFLAGS= -Og -std=c++17

SOURCES = hangman.cpp main.cpp

OBJS = hangman.o main.o

TARGET = main

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJS) : %.o : %.cpp

clean : 
	rm -f $(TARGET) $(OBJS)
