#ifndef __QTG_ENTITY_HPP__

#define __QTG_ENTITY_HPP__

#include "defines.hpp"

namespace qtg {

typedef struct _MoveInfo {
  bool wantMove;
  map_size_t moveCount;
  Direnction moveDir;
  _MoveInfo(const struct _MoveInfo &src) = default;
  _MoveInfo(struct _MoveInfo &&src) = default;
  _MoveInfo(): wantMove(false), moveCount(0), moveDir(Direnction::UP) {}
  struct _MoveInfo &operator=(const struct _MoveInfo &src) = default;
  struct _MoveInfo &operator=(struct _MoveInfo &&src) = default;
  bool operator==(const _MoveInfo &src) const {
    return src.wantMove == wantMove && src.moveCount == moveCount &&
           src.moveDir == moveDir;
  }
} MoveInfo;

class Entity {
public:
  Vector2i pos;
  MoveInfo moveInfo;
  AABB box;
  Entity(Vector2i pos): pos(pos), moveInfo(), box() {}
  virtual ~Entity() {}

  QTG_INLINE bool want_move() const noexcept { return moveInfo.wantMove; }
  QTG_INLINE map_size_t get_move_count() const noexcept {
    return moveInfo.moveCount;
  }
  QTG_INLINE Direnction get_move_direnction() const noexcept {
    return moveInfo.moveDir;
  }

  QTG_INLINE void set_want_move(bool want) noexcept {
    moveInfo.wantMove = want;
  }

  QTG_INLINE void set_move_count(map_size_t moveCount) noexcept {
    moveInfo.moveCount = moveCount;
  }
  QTG_INLINE void set_move_dir(Direnction dir) noexcept {
    moveInfo.moveDir = dir;
  }

  virtual Entity *copy() const = 0;

  virtual void on_start_move() = 0;
  virtual void on_end_move() = 0;

  virtual bool operator==(const Entity &src) const noexcept {
    return src.box == box && src.moveInfo == moveInfo && src.pos == pos;
  }
};

} // namespace qtg

#endif /* end of include guard: __QTG_ENTITY_HPP__ */
