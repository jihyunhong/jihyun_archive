CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = virtual_exe
OBJECTS = main.o rule_of_three.o

all : $(TARGET)

$(OBJECTS): %.o : %.cpp 
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)