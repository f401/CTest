#include "linux.h"
#include "gameData.hpp"
#include "entity.hpp"
#include <iostream>
#include <stdlib.h>
#include <termios.h>

using namespace qtg;

void gaming(Entity& src) {
	for (;;) {
		std::cout << std::endl;
		src.getGameData().print();
		char ch = getchar();
		switch (ch) {
			case 'w':
				src.move_up();
				break;
			case 'a':
				src.move_left();
				break;
			case 's':
				src.move_down();
				break;
			case 'd':
				src.move_right();
				break;
			default:
				return;
		}
	}
}

int main(int argc, char *argv[]) {
  set_stdin_no_buffer();
  GameData game(10, 20);
  Entity entity(1, game);
  game.make_wall_unthrought(Vector2i(1, 1));
  game.make_out_area_unthought();
  game.add_entity(Vector2i(2, 2), 1);
  game.add_entity(Vector2i(1, 2), 1);
  gaming(entity);
  return 0;
}
