#include "game.hpp"

using namespace qtg;

Game::Game(map_size_t x, map_size_t y) : __x(x), __y(y) {
  x += 2;
  y += 2;
  {
    __blocks = new Block **[x];
    for (map_size_t i = 0; i <= x; ++i) {
      __blocks[i] = new Block *[y];
      for (map_size_t j = 0; j <= y; ++j) {
        if (i == 0 || i == x || j == 0 || j == y) {
          __blocks[i][j] = new UnthroughBlock(i, j);
        } else {
          __blocks[i][j] = new Block(i, j);
        }
      }
    }
  }
}

Game::~Game() {
  for (map_size_t i = 0; i <= __x + 2; ++i) {
    for (map_size_t j = 0; j <= __y + 2; ++j) {
      delete __blocks[i][j];
    }
    delete[] __blocks[i];
  }
  delete[] __blocks;
}

void Game::register_entity(Entity &entity, Vector2i initPos) {
	__entities.add(entity);
}
