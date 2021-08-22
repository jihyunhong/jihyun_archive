CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = elseif
OBJECTS = elseif.o
DEPS:= 

all : $(TARGET)

$(OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)