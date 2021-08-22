CC = g++ -std=c++17
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = StudentScore
OBJECTS = student.o main.o
DEPS:=

all : $(TARGET)

$(OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)
	rm -rf StudentScore.dSYM/
