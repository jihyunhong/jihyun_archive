CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og

ONE= 1/rectangle.cpp
TWO= 2/elipse.cpp
THREE= 3/main.cpp 3/exchange.cpp

ONE_TARGET = rectangle
TWO_TARGET = elipse
THREE_TARGET = exchange

ONE_OBJECTS = 1/rectangle.o
TWO_OBJECTS = 2/elipse.o
THREE_OBJECTS = 3/main.o 3/exchange.o

DEPS:= 

all : one two three

$(ONE_OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TWO_OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(THREE_OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

one : $(ONE_OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $(ONE_TARGET) $^

two : $(TWO_OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $(TWO_TARGET) $^

three : $(THREE_OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $(THREE_TARGET) $^

clean :
	rm -rf $(ONE_OBJECTS) $(TWO_OBJECTS) $(THREE_OBJECTS) $(ONE_TARGET) $(TWO_TARGET) $(THREE_TARGET)

