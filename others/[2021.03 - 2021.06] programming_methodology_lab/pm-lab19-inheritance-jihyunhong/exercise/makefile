all: clean test

appTests: tests.cpp inheritance.hpp
	g++ -fsanitize=address --std=c++17 tests.cpp -o appTests

test: appTests
	# executes all tests
	./appTests

clean:
	rm -f appTests
