CC = g++
CFLAGS = -W -Wall
TARGET = Shape
OBJECT = circle.o shape.o square.o triangle.o main.o

all : $(TARGET)

$(TARGET) : $(OBJECT)
	$(CC) $(CFLAGS) -o $@ $^

clean : 
	rm -rf *.o $(TARGET)