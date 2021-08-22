CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = doubly_linked_list
OBJECTS = main.o doubly_linked_list.o

all : $(TARGET)

$(OBJECTS): %.o : %.cpp 
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)