#include "Tokenizer.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	jsparser::Tokenizer izer("wword ala");
	izer.nextToken();
	std::cout << std::endl << (int) izer.nextToken() << std::endl;
	izer.nextToken();
	std::cout <<  (int) izer.nextToken() << std::endl;
	return 0;
}
