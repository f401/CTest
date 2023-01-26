#include "defines.hpp"
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

void set_stdin_no_blocking() {
  struct termios tios;
  int id = tcgetattr(0, &tios);
  if (id == -1)
    perror("tcgetattr");
  tios.c_lflag &= ~(ICANON);
  tcsetattr(0, TCSAFLUSH, &tios);
}

int main(int argc, char *argv[]) {
  set_stdin_no_blocking();
  game(qtg::GameData(10, 20));
  return 0;
}
