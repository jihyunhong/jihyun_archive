CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = if
OBJECTS = if.o
DEPS:= 

all : $(TARGET)

$(OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)