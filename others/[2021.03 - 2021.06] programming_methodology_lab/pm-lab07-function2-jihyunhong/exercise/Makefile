CC = g++
CFLAGS = -W
CCFLAGS= -Og
TARGET = hanoi 
OBJECTS = hanoi.o
#OBJECTS = answer.o
DEPS:=

all : $(TARGET)

$(OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)
