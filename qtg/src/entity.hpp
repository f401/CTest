#ifndef __QTG_ENTITY__

#define __QTG_ENTITY__

#include "gameData.hpp"

using namespace qtg;

class Entity {
public:
  Entity(entity_id_t id, GameData &data) : __id(id), __gameData(data) {}

  void move_up() const noexcept { __gameData.move_up(__id); }
  void move_down() const noexcept { __gameData.move_down(__id); }
  void move_right() const noexcept { __gameData.move_right(__id); }
  void move_left() const noexcept { __gameData.move_left(__id); }

  void register_entity(const Vector2i &pos) const noexcept { __gameData.add_entity(pos, __id); }

  vector2i_list get_up() const noexcept { return __gameData.get_up(__id); }
  vector2i_list get_left() const noexcept { return __gameData.get_left(__id); }
  vector2i_list get_down() const noexcept { return __gameData.get_down(__id); }
  vector2i_list get_right() const noexcept {
    return __gameData.get_right(__id);
  }

  const GameData &getGameData() const noexcept { return __gameData; }

  entity_id_t get_id() const noexcept { return __id; }

private:
  entity_id_t __id;
  GameData &__gameData;
};

#endif /* end of include guard: __QTG_ENTITY__ */
