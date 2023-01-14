#include "defines.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	qtg::GameData gameData(10, 20);
	qtg::Vector2i i(atoi(argv[1]), atoi(argv[2]));
	gameData.add_entity(i, 1);
	gameData.moveUpOne(1);
	cout << "x: " << i.x << ", y: " << i.y << endl;
	gameData.print();
	return 0;
}

