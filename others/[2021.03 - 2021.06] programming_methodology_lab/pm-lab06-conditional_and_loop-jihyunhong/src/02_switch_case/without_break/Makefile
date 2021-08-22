CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = without_break
OBJECTS = without_break.o
DEPS:= 

all : $(TARGET)

$(OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)