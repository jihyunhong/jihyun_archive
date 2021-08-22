CC = g++ -std=c++17
CFLAGS = -W
CCFLAGS= -Og
TARGET = game_file
OBJECTS = main.o poke_DS.o pokemon.o battle.o configure.o

all : $(TARGET)

$(OBJECTS): %.o : %.cpp
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)