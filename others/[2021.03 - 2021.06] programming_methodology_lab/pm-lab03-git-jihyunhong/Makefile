CC = g++
CFLAGS = -W -Wall
CCFLAGS= -Og
TARGET = helloworld
OBJECTS = helloworld.o
DEPS:=

all : $(TARGET)

$(OBJECTS): %.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)

$(TARGET) : $(OBJECTS) $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf *.o $(TARGET)

#본인의 학번을 입력해주세요
id:
	@echo "2018-12130"
 
lab:
	@echo "03 git"
 
