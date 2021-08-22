CC = g++ -std=c++17
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = shape
OBJECTS = main.o shape.o

all : $(TARGET)

$(OBJECTS): %.o : %.cpp 
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)