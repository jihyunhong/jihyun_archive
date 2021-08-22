CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = break
OBJECTS = break.o
DEPS:= 

all : $(TARGET)

$(OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)