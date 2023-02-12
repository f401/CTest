#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "Card.hpp"

__attribute__((constructor(101))) void makeRandSeed() {
  srand(time(0));
}

int main(int argc, char *argv[])
{
	ddz::CardList list = ddz::makeFullCardList();
	list.shuffle();
	list.sort();
	for (ddz::Card card: list) {
		std::cout << "displayNum: " << card.displayNum.cppStr() << ", Real: " << card.realNum << std::endl;
	}
	std::cout << list.size() << std::endl;
	return 0;
}
