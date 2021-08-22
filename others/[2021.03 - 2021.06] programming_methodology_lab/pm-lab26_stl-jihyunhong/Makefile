CC = g++
CFLAGS = -W
CCFLAGS= -Og -std=c++17
TARGET = main 
OBJECTS = main.o
DEPS:=

all : $(TARGET)

$(OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)
