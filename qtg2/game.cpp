#include "game.hpp"

using namespace qtg;

#define ALLOC_BLOCKS(block, x_len, y_len)                                      \
  {                                                                            \
    block = new Block *[x_len];                                                \
    for (map_size_t _y = 0; _y <= y_len; ++_y) {                               \
      block[_y] = new Block[y_len];                                            \
    }                                                                          \
  }

Game::Game(map_size_t x, map_size_t y) : __x(x), __y(y) {
  x += 2;
  y += 2;
  ALLOC_BLOCKS(__blocks, x, y);
  for (map_size_t i = 0; i < x; ++i) {
    for (map_size_t j = 0; j < y; ++j) {
      __blocks[i][j].pos = Vector2i(i, j);
    }
  }
}
