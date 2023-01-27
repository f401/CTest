#include "defines.hpp"
#include "linux.h"
#include <iostream>
#include <stdlib.h>
#include <termios.h>

using namespace std;

#define PRINT_LIST(src)                                                        \
  for (auto i = src.cbegin(); i != src.cend(); ++i) {                          \
    cout << i->x << ", " << i->y << endl;                                      \
  }

void game(qtg::GameData &&gd) {
  gd.add_entity(qtg::Vector2i(10, 20), 1);
  gd.print();
  for (;;) {
    char src = getchar();
    switch (src) {
    case 'w':
      gd.move_up(1);
      break;
    case 'a':
      gd.move_left(1);
      break;
    case 's':
      gd.move_down(1);
      break;
    case 'd':
      gd.move_right(1);
      break;
    default:
      return;
    }
    gd.print();
    cout << "\n";
  }
}

int main(int argc, char *argv[]) {
  set_stdin_no_buffer();
  game(qtg::GameData(10, 20));
  return 0;
}
