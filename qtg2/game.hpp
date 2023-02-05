#ifndef __QTG_GAME_HPP__

#define __QTG_GAME_HPP__

#include "block.hpp"
#include "entity.hpp"
#include "entity_list.hpp"
#include <iostream>
#include <vector>

namespace qtg {

class Game final {
public:
  Game(map_size_t x, map_size_t y);
  ~Game();

  void register_entity(Entity &entity, Vector2i initPos); 

  void print() {
    for (map_size_t i = 1; i <= __y; ++i) {
      for (map_size_t j = 1; j <= __x; ++j) {
        std::cout << (int)__blocks[j][i]->on_entity_move_here() << " ";
      }
      std::cout << std::endl;
    }
  }
  bool chkAABB(AABB box, Vector2i pos);
private:
  map_size_t __x, __y;
  Block ***__blocks;
  EntityList __entities;
};

}; // namespace qtg

#endif /* end of include guard: __QTG_GAME_HPP__ */
