CC = g++
CFLAGS = -W
CCFLAGS= -Og --std=c++14
TARGET = SNUMusic
OBJECTS = bank.o card.o client.o music.o SNUMusicSystem.o main.o
DEPS:=

all : $(TARGET)

$(OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ -g $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ -g $^

clean :
	rm -rf *.o $(TARGET)
