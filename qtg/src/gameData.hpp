#ifndef __QTG_GAMEDATA_HPP__

#define __QTG_GAMEDATA_HPP__

#include "defines.hpp"

namespace qtg {

class GameData {
public:
  GameData(map_size_t x_len, map_size_t y_len);
  GameData(const GameData &data);
  GameData(GameData &&data);
  GameData& operator=(const GameData &src);
  GameData& operator=(GameData &&src);
  ~GameData();

  Block &get(const Vector2i &pos) const {
    chk_pos(pos);
    return __data[pos.x][pos.y];
  }

  bool has_entity(const Vector2i &pos) const {
    chk_pos(pos);
    return __data[pos.x][pos.y].entities.size() != 0;
  }

  void add_entity(const Vector2i &pos, entity_id_t id) const {
    chk_pos(pos);
    __data[pos.x][pos.y].entities.add(id);
  }

  void remove_entity(const Vector2i &pos) {
	  chk_pos(pos);
	  __data[pos.x][pos.y].entities.clear();
  }

  void remove_entity(const Vector2i &pos, entity_id_t id) {
	  chk_pos(pos);
	  __data[pos.x][pos.y].entities.remove(id);
  }

  entity_list &get_entities(const Vector2i &pos) const {
    chk_pos(pos);
    return __data[pos.x][pos.y].entities;
  }

  void make_wall_unthrought(const Vector2i &pos);
  void make_out_area_unthrought();

  map_size_t x_len() const noexcept { return __x_len; }
  map_size_t y_len() const noexcept { return __y_len; }

  void move_up(entity_id_t entity_id);
  void move_down(entity_id_t entity_id);
  void move_right(entity_id_t entity_id);
  void move_left(entity_id_t entity_id);

  vector2i_list get_up(entity_id_t entity_id) const;
  vector2i_list get_left(entity_id_t entity_id) const;
  vector2i_list get_right(entity_id_t entity_id) const;
  vector2i_list get_down(entity_id_t entity_id) const;
#ifdef DEBUG
  void print() const {
    for (int j = 1; j <= __y_len; ++j) {
      for (int i = 1; i <= __x_len; ++i) {
        std::cout << __data[i][j].entities << " ";
      }
      std::cout << std::endl;
    }
  }
#endif

private:
  void do_out_area_clean();

  void chk_pos(const Vector2i &src) const {
    if (src.x > __x_len || src.y > __y_len)
      throw std::out_of_range("Index Out, x: " + std::to_string(src.x) +
                              ",y :" + std::to_string(src.y) +
                              ", but x_len: " + std::to_string(__x_len) +
                              ", y_len: " + std::to_string(__y_len));
  }

  Block **__data;
  map_size_t __x_len, __y_len;
  bool out_area_throught;
};
} // namespace qtg
#endif /* end of include guard: __QTG_GAMEDATA_HPP__ */
