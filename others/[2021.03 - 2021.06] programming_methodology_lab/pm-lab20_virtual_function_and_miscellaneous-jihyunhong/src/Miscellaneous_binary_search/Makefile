CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = binary_search
OBJECTS = main.o binary_search.o

all : $(TARGET)

$(OBJECTS): %.o : %.cpp 
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)