CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = Insertionsort_exe
OBJECTS = Insertionsort.o main.o
DEPS:= Insertionsort.h

all : $(TARGET)

$(OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)