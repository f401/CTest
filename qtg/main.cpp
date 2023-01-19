#include "defines.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	qtg::GameData gameData(10, 20);
	qtg::Vector2i i(atoi(argv[1]), atoi(argv[2]));
	gameData.add_entity(i, 1);
	cout << "x: " << i.x << ", y: " << i.y << endl;
	gameData.print();
	cout << "x: " << i.x << ", y: " << i.y << endl;
	gameData.moveDownOne(1);
	gameData.moveLeftOne(1);
	gameData.print();
	gameData.moveRightOne(1);
	gameData.print();
	return 0;
}

