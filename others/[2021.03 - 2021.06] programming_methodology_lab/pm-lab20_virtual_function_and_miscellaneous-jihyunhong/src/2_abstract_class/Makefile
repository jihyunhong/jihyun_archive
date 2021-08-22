CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = virtual_exe
OBJECTS = main.o shape.o

all : $(TARGET)

$(OBJECTS): %.o : %.cpp
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)