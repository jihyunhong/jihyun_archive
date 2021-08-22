CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = your_first_cpp_exe
OBJECTS = your_first_cpp.o
DEPS:=

all : $(TARGET)

$(OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)