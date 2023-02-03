#ifndef __QTG_BLOCK_HPP__

#define __QTG_BLOCK_HPP__

#include "defines.hpp"

namespace qtg {

class Block {
public:
  Block(map_size_t x, map_size_t y): pos(x, y) {}
  Block(Vector2i pos): pos(pos) {}
  Block(): Block(0, 0) {}

  Vector2i pos;

  //return true allow move
  virtual bool on_entity_move_here() { return true; }
};

} // namespace qtg

#endif /* end of include guard: __QTG_BLOCK_HPP__ */
