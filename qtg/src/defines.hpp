#ifndef __PTG_DEFINES_HPP__
#define __PTG_DEFINES_HPP__

#include <algorithm>
#include <iostream>
#include <ostream>
#include <stdint.h>
#include <vector>

#define DEBUG

namespace qtg {

typedef uint32_t map_size_t;
typedef uint16_t entity_size_t;
typedef uint16_t entity_id_t;

class GameData;

#define ENTITY_EMPTY 0
class entity_list : std::vector<entity_id_t> {
public:
  using std::vector<entity_id_t>::size;
  using std::vector<entity_id_t>::operator[];
  using std::vector<entity_id_t>::operator=;
  using std::vector<entity_id_t>::vector;
  using std::vector<entity_id_t>::clear;
  using std::vector<entity_id_t>::const_iterator;
  using std::vector<entity_id_t>::cbegin;
  using std::vector<entity_id_t>::cend;

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

  bool has(entity_id_t id) const {
    if (size() == 0)
      return false;
    return std::count(cbegin(), cend(), id);
  }

#ifdef DEBUG
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
#endif
};

struct Vector2i {
  map_size_t x, y;
  Vector2i(map_size_t _x, map_size_t _y) : x(_x), y(_y) {}

  struct Vector2i up() { return Vector2i(x, y - 1); }

  struct Vector2i down() { return Vector2i(x, y + 1); }

  struct Vector2i right() { return Vector2i(x + 1, y); }

  struct Vector2i left() { return Vector2i(x - 1, y); }
};

typedef std::vector<struct Vector2i> vector2i_list;

struct Block {
  struct Vector2i pos;
  entity_list entities;
  // 返回true表示允许move到当前block
  bool (*on_entity_move_here)(Block &current, entity_id_t id);
};

#ifdef DEBUG
std::ostream &operator<<(std::ostream &stream, Block &blk);
#endif

} // namespace qtg
#endif
