#include "defines.hpp"
#include <stdlib.h>

using namespace qtg;

GameData::GameData(map_size_t x_len, map_size_t y_len)
    : __x_len(x_len), __y_len(y_len) {
  x_len += 2;
  y_len += 2;
  // alloc data
  __data = (Block **)malloc(sizeof(Block *) * x_len);
  for (map_size_t i = 0; i < x_len; ++i) {
    __data[i] = (Block *)malloc(sizeof(struct Block) * y_len);
  }
  // init data
  for (map_size_t i = 0; i < x_len; ++i) {
    for (map_size_t j = 0; j < y_len; ++j) {
      __data[i][j].entities = entity_list();
      __data[i][j].pos.x = i;
      __data[i][j].pos.y = j;
      __data[i][j].on_entity_move_here = NULL;
    }
  }
}

GameData::~GameData() {
  map_size_t x_len = __x_len + 2, y_len = __y_len + 2;
  for (map_size_t i = 0; i < x_len; ++i) {
      free(__data[i]);
  }
  free(__data);
}

void GameData::do_out_area_clean() {
  for (map_size_t i = 0; i <= __y_len + 1; ++i) {
    __data[0][i].entities.clear();
  }

  for (map_size_t i = 0; i <= __y_len + 1; ++i) {
    __data[__x_len + 1][i].entities.clear();
  }

  for (map_size_t i = 0; i <= __x_len + 1; ++i) {
    __data[i][0].entities.clear();
  }

  for (map_size_t i = 0; i <= __x_len + 1; ++i) {
    __data[i][__y_len + 1].entities.clear();
  }
}

#define DO_MOVE(i, j, dir)                                                     \
  struct Block &blk = __data[i][j];                                            \
  entity_list &entities = blk.entities;                                        \
  if (entities.has(entity_id)) {                                               \
    struct Vector2i where = blk.pos.dir();                                     \
    struct Block &target = __data[where.x][where.y];                           \
                                                                               \
    bool allowMove = true;                                                     \
    if (target.on_entity_move_here != NULL) {                                  \
      allowMove = target.on_entity_move_here(entity_id);                       \
    }                                                                          \
                                                                               \
    if (allowMove) {                                                           \
      blk.entities.remove(entity_id);                                          \
      target.entities.add(entity_id);                                          \
      do_out_area_clean();                                                     \
    }                                                                          \
  }

void GameData::move_up(entity_id_t entity_id) {
  for (map_size_t i = 1; i <= __x_len; ++i) {
    for (map_size_t j = 1; j <= __y_len; ++j) {
      DO_MOVE(i, j, up);
    }
  }
}

void GameData::move_down(entity_id_t entity_id) {
  for (map_size_t i = __x_len; i > 0; --i) {
    for (map_size_t j = __y_len; j > 0; --j) {
      DO_MOVE(i, j, down);
    }
  }
}

void GameData::move_right(entity_id_t entity_id) {
  for (map_size_t i = __x_len; i > 0; --i) {
    for (map_size_t j = 1; j <= __y_len; ++j) {
      DO_MOVE(i, j, right);
    }
  }
}

void GameData::move_left(entity_id_t entity_id) {
  for (map_size_t i = 1; i <= __x_len; ++i) {
    for (map_size_t j = __y_len; j > 0; --j) {
      DO_MOVE(i, j, left);
    }
  }
}

vector2i_list GameData::get_up(entity_id_t entity_id) const {
  vector2i_list result = vector2i_list();
  for (map_size_t i = 1; i <= __x_len; ++i) {
    for (map_size_t j = 1; j <= __y_len; ++j) {
      Block &target = __data[i][j];
      if (target.entities.has(entity_id)) {
        result.push_back(target.pos);
        break;
      }
    }
  }
  return result;
}

vector2i_list GameData::get_down(entity_id_t entity_id) const {
  vector2i_list result = vector2i_list();
  for (map_size_t i = 1; i <= __x_len; ++i) {
    for (map_size_t j = __y_len; j > 0; --j) { // changed
      Block &target = __data[i][j];
      if (target.entities.has(entity_id)) {
        result.push_back(target.pos);
        break;
      }
    }
  }
  return result;
}

vector2i_list GameData::get_left(entity_id_t entity_id) const {
  vector2i_list result = vector2i_list();
  for (map_size_t i = 1; i <= __y_len; ++i) {   // changed
    for (map_size_t j = 1; j <= __x_len; ++j) { // changed
      Block &target = __data[j][i];             // changed
      if (target.entities.has(entity_id)) {
        result.push_back(target.pos);
        break;
      }
    }
  }
  return result;
}

vector2i_list GameData::get_right(entity_id_t entity_id) const {
  vector2i_list result = vector2i_list();
  for (map_size_t i = 1; i <= __y_len; ++i) {
    for (map_size_t j = __x_len; j > 0; --j) { // changed
      Block &target = __data[j][i];
      if (target.entities.has(entity_id)) {
        result.push_back(target.pos);
        break;
      }
    }
  }
  return result;
}
