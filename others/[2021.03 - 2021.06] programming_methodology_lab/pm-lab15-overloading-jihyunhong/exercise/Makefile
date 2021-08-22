all: clean appTests

appTests:
	g++ -fsanitize=address --std=c++17 tests.cpp double_vector.cpp -o appTests

test: appTests
	./appTests

clean:
	rm -f appTests
