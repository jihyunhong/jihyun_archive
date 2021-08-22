/* This code adds two input numbers and print out sum of them. */

#include <iostream>
 

int readNumber(int x)
{
	std::cout << "Please enter a number: ";
	std::cin >> x;
	return x;
}
 
void writeAnswer(int x)
{
	std::cout << "The sum is " << x << std::endl;
}
 
int main()
{
	int x = 0;
	x = readNumber(x);
	x = x + readNumber(x);
	writeAnswer(x);
 
	return 0;
}
