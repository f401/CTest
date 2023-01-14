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

std::ostream &operator<<(std::ostream &stream, Block &blk) {
  stream << "Block {"
         << "x: " << blk.pos.x << ",y :" << blk.pos.y
         << ", entity_id: " << blk.entities
         << ", has_func: " << (blk.on_entity_move_here == NULL) << "}";
  return stream;
}

void GameData::moveUpOne(entity_id_t entity_id) {
  for (map_size_t i = 1; i <= __x_len; ++i) {
    for (map_size_t j = 1; j <= __y_len; ++j) {
      struct Block &blk = __data[i][j];
      entity_list &entities = blk.entities;
      if (entities.has(entity_id)) {
        struct Vector2i up = blk.pos.up();
        struct Block &target = __data[up.x][up.y];

        bool allowMove = true;
        if (target.on_entity_move_here != NULL) {
          allowMove = target.on_entity_move_here(entity_id);
        }

        if (allowMove) {
          blk.entities.remove(entity_id);
          target.entities.add(entity_id);
        }
      }
    }
  }
}
