#include "gameData.hpp"
#include <stdlib.h>
#include <string.h>

    using namespace qtg;

#define ALLOC_GAME_DATA(data, x_len, y_len)                                    \
  {                                                                            \
    data = (Block **)malloc(sizeof(Block *) * x_len);                          \
    for (map_size_t i = 0; i < x_len; ++i) {                                   \
      data[i] = (Block *)malloc(sizeof(struct Block) * y_len);                 \
    }                                                                          \
  }

#define FREE_GAME_DATA()                                                       \
  {                                                                            \
    map_size_t x_len = __x_len + 2, y_len = __y_len + 2;                       \
    for (map_size_t i = 0; i < x_len; ++i) {                                   \
      free(__data[i]);                                                         \
    }                                                                          \
    free(__data);                                                              \
  }

GameData::GameData(map_size_t x_len, map_size_t y_len)
    : __x_len(x_len), __y_len(y_len), out_area_throught(true) {
  x_len += 2;
  y_len += 2;
  // alloc data
  ALLOC_GAME_DATA(__data, x_len, y_len);
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

GameData::GameData(const GameData &data)
    : __x_len(data.__x_len), __y_len(data.__y_len) {
  map_size_t x_len = __x_len + 2, y_len = __y_len + 2;
  ALLOC_GAME_DATA(__data, x_len, y_len);
  for (map_size_t i = 0; i < x_len; ++i) {
    for (map_size_t j = 0; j < y_len; ++j) {
      __data[i][j] = data.__data[i][j];
    }
  }
}
GameData::GameData(GameData &&data)
    : __x_len(data.__x_len), __y_len(data.__y_len), __data(data.__data) {
  data.__data = nullptr;
}
GameData &GameData::operator=(const GameData &src) {
  if (this != &src) {
    FREE_GAME_DATA();
    __x_len = src.__x_len;
    __y_len = src.__y_len;
    for (map_size_t i = 0; i < __x_len + 2; ++i) {
      for (map_size_t j = 0; j < __y_len + 2; ++j) {
        __data[i][j] = src.__data[i][j];
      }
    }
  }
  return *this;
}
GameData &GameData::operator=(GameData &&src) {
  __x_len = src.__x_len;
  __y_len = src.__y_len;
  __data = src.__data;
  src.__data = nullptr;
  return *this;
}

GameData::~GameData() { FREE_GAME_DATA() }

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

static bool __false(entity_id_t id) { return false; }

void GameData::make_wall_unthrought(const Vector2i &pos) {
  chk_pos(pos);
  __data[pos.x][pos.y].on_entity_move_here = &__false;
}

void GameData::make_out_area_unthrought() {
  out_area_throught = false;
  for (map_size_t i = 0; i <= __y_len + 1; ++i) {
    __data[0][i].on_entity_move_here = &__false;
  }

  for (map_size_t i = 0; i <= __y_len + 1; ++i) {
    __data[__x_len + 1][i].on_entity_move_here = &__false;
  }

  for (map_size_t i = 0; i <= __x_len + 1; ++i) {
    __data[i][0].on_entity_move_here = &__false;
  }

  for (map_size_t i = 0; i <= __x_len + 1; ++i) {
    __data[i][__y_len + 1].on_entity_move_here = &__false;
  }
}

#define CHECK_CAN_MOVE(i, j, dir, needMoveList, canMove, endLoop)              \
  struct Block &blk = __data[i][j];                                            \
  entity_list &entities = blk.entities;                                        \
  if (entities.has(entity_id)) {                                               \
    struct Vector2i where = blk.pos.dir();                                     \
    struct Block &target = __data[where.x][where.y];                           \
                                                                               \
    if (target.on_entity_move_here != NULL) {                                  \
      canMove = target.on_entity_move_here(entity_id);                         \
    }                                                                          \
    if (!canMove) {                                                            \
      goto endLoop;                                                            \
    } else {                                                                   \
      needMoveList.push_back(std::make_pair(&blk, &target));                   \
    }                                                                          \
  }

#define DO_MOVE(needMoveList, entity_id)                                       \
  for (auto i = needMoveList.begin(); i != needMoveList.end(); ++i) {          \
    i->first->entities.remove(entity_id);                                       \
    i->second->entities.add(entity_id);                                         \
  }

void GameData::move_up(entity_id_t entity_id) {
  // 使用指针防止拷贝
  std::vector<std::pair<Block *, Block *>> needMoveList =
      std::vector<std::pair<Block *, Block *>>(); // std::pair<from, to>
  bool canMove = true;
  for (map_size_t i = 1; i <= __x_len; ++i) {
    for (map_size_t j = 1; j <= __y_len; ++j) {
      CHECK_CAN_MOVE(i, j, up, needMoveList, canMove, endLoop);
    }
  }
endLoop:
  DO_MOVE(needMoveList, entity_id);
}

void GameData::move_down(entity_id_t entity_id) {
  std::vector<std::pair<Block *, Block *>> needMoveList =
      std::vector<std::pair<Block *, Block *>>(); // std::pair<from, to>
  bool canMove = true;
  for (map_size_t i = __x_len; i > 0; --i) {
    for (map_size_t j = __y_len; j > 0; --j) {
      CHECK_CAN_MOVE(i, j, down, needMoveList, canMove, endLoop);
    }
  }
endLoop:
  DO_MOVE(needMoveList, entity_id);
}

void GameData::move_right(entity_id_t entity_id) {
  std::vector<std::pair<Block *, Block *>> needMoveList =
      std::vector<std::pair<Block *, Block *>>(); // std::pair<from, to>
  bool canMove = true;
  for (map_size_t i = __x_len; i > 0; --i) {
    for (map_size_t j = 1; j <= __y_len; ++j) {
      CHECK_CAN_MOVE(i, j, right, needMoveList, canMove, endLoop);
    }
  }
endLoop:
  DO_MOVE(needMoveList, entity_id);
}

void GameData::move_left(entity_id_t entity_id) {
  std::vector<std::pair<Block *, Block *>> needMoveList =
      std::vector<std::pair<Block *, Block *>>(); // std::pair<from, to>
  bool canMove = true;
  for (map_size_t i = 1; i <= __x_len; ++i) {
    for (map_size_t j = __y_len; j > 0; --j) {
      CHECK_CAN_MOVE(i, j, left, needMoveList, canMove, endLoop);
    }
  }
endLoop:
  DO_MOVE(needMoveList, entity_id);
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
