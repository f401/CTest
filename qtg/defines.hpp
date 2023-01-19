#ifndef __PTG_DEFINES_HPP__
#define __PTG_DEFINES_HPP__

#include <algorithm>
#include <iostream>
#include <ostream>
#include <stdint.h>
#include <vector>

namespace qtg {

typedef uint32_t map_size_t;
typedef uint16_t entity_size_t;
typedef uint16_t entity_id_t;

#define ENTITY_EMPTY 0

class entity_list : std::vector<entity_id_t> {
public:
  using std::vector<entity_id_t>::size;
  using std::vector<entity_id_t>::operator[];
  using std::vector<entity_id_t>::operator=;
  using std::vector<entity_id_t>::vector;
  using std::vector<entity_id_t>::clear;

  void remove(entity_id_t id) {
    auto result = std::find(this->begin(), this->end(), id);
    if (id == *result || result != this->end()) {
      this->erase(result);
    }
  }

  void add(entity_id_t id) {
    if (size() == 0 || !has(id)) {
      push_back(id);
    }
  }

  bool has(entity_id_t id) {
    if (size() == 0)
      return false;
    return id == *this->end() ||
           std::find(this->begin(), this->end(), id) != this->end();
  }

  friend std::ostream &operator<<(std::ostream &out, entity_list &src) {
    if (src.size() == 1) {
      out << src[0];
    } else if (src.size() == 0) {
      out << "0";
    } else {
      for (auto i = src.cbegin(); i != src.cend(); ++i) {
        out << *i << "/";
      }
    }
    return out;
  }
};

struct Vector2i {
  map_size_t x, y;
  Vector2i(map_size_t _x, map_size_t _y) : x(_x), y(_y) {}

  struct Vector2i up() {
    return Vector2i(x, y - 1);
  }

  struct Vector2i down() {
    return Vector2i(x, y + 1);
  }

  struct Vector2i right() {
    return Vector2i(x + 1, y);
  }

  struct Vector2i left() {
    return Vector2i(x - 1, y);
  }
};

struct Block {
  struct Vector2i pos;
  entity_list entities;
  //返回true表示允许move到当前block
  bool (*on_entity_move_here)(entity_id_t id);
};

std::ostream &operator<<(std::ostream &stream, Block &blk);

class GameData {
public:
  GameData(map_size_t x_len, map_size_t y_len);

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

  entity_list &get_entity(const Vector2i &pos) const {
    chk_pos(pos);
    return __data[pos.x][pos.y].entities;
  }

  map_size_t x_len() const noexcept { return __x_len; }
  map_size_t y_len() const noexcept { return __y_len; }

  void moveUpOne(entity_id_t entity_id);
  void moveDownOne(entity_id_t entity_id);
  void moveRightOne(entity_id_t entity_id);
  void moveLeftOne(entity_id_t entity_id);

  void print() {
    for (int j = 1; j <= __y_len; ++j) {
      for (int i = 1; i <= __x_len; ++i) {
        std::cout << __data[i][j].entities << " ";
      }
      std::cout << std::endl;
    }
  }

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
};

} // namespace qtg
#endif
