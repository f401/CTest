#ifndef __QTG_BLOCK_HPP__

#define __QTG_BLOCK_HPP__

#include "defines.hpp"

namespace qtg {

class Block {
public:
  Vector2i pos;

  virtual bool on_entity_move_here() = 0;
};

} // namespace qtg

#endif /* end of include guard: __QTG_BLOCK_HPP__ */
