#ifndef __QTG_DEFINES_H__

#define __QTG_DEFINES_H__

#include <stdint.h>

namespace qtg {

typedef uint32_t map_size_t;

#define QTG_INLINE inline

typedef struct _Vector2i {
  map_size_t x, y;
  _Vector2i(map_size_t _x, map_size_t _y) : x(_x), y(_y) {}

  _Vector2i up() { return _Vector2i(x, y - 1); }
  _Vector2i down() { return _Vector2i(x, y + 1); }
  _Vector2i right() { return _Vector2i(x + 1, y); }
  _Vector2i left() { return _Vector2i(x - 1, y); }

  bool operator==(const _Vector2i &src) const {
    return src.x == x && src.y == y;
  }

} Vector2i;

enum class Direnction { UP, DOWN, LEFT, RIGHT };

typedef struct _AABB {
  map_size_t x0, x1, y0, y1;
  _AABB(map_size_t x0, map_size_t x1, map_size_t y0, map_size_t y1)
      : x0(x0), x1(x1), y0(y0), y1(y1) {}
  _AABB() 
      : x0(0), x1(0), y0(0), y1(0) {}

  bool operator==(const _AABB &src) const {
    return src.x0 == x0 && src.x1 == x1 && src.y0 == y0 && src.y1 == y1;
  }
} AABB;

} // namespace qtg

#endif /* end of include guard: __QTG_DEFINES_H__ */
