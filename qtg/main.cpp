#include "defines.hpp"
#include <iostream>

using namespace std;

#define PRINT_LIST(src)                                                        \
  for (auto i = src.cbegin(); i != src.cend(); ++i) {                          \
    cout << i->x << ", " << i->y << endl;                                      \
  }

int main(int argc, char *argv[]) {
  qtg::GameData gameData(10, 20);
  gameData.add_entity(qtg::Vector2i(2, 2), 1);
  gameData.add_entity(qtg::Vector2i(2, 3), 1);
  gameData.add_entity(qtg::Vector2i(3, 2), 1);
  gameData.add_entity(qtg::Vector2i(3, 3), 1);
  gameData.print();
  cout << endl;
  qtg::vector2i_list up = gameData.get_up(1);
  PRINT_LIST(up);
  qtg::vector2i_list down = gameData.get_down(1);
  cout << endl;
  PRINT_LIST(down);
  qtg::vector2i_list left = gameData.get_left(1);
  cout << endl;
  PRINT_LIST(left);
  qtg::vector2i_list right = gameData.get_right(1);
  cout << endl;
  PRINT_LIST(right);
  return 0;
}
