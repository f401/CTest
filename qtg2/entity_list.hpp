#ifndef __QTG_ENTITY_LIST_HPP__

#define __QTG_ENTITY_LIST_HPP__

#include "entity.hpp"
#include <algorithm>
#include <vector>

namespace qtg {

class EntityList {
public:
  EntityList() : __list() {}
  ~EntityList() {
    for (auto i : __list) {
      delete i;
    }
  }
  QTG_INLINE size_t size() const noexcept { return __list.size(); }

  QTG_INLINE void add(const Entity &src) { __list.push_back(src.copy()); }

  QTG_INLINE bool has(const Entity &src) const {
    if (__list.size() != 0) {
      for (auto i : __list) {
        if (*i == src)
          return true;
      }
    }
    return false;
  }

  QTG_INLINE void remove(const Entity &src) {
    if (__list.size() != 0) {
      for (std::vector<Entity *>::iterator i = __list.begin();
           i != __list.end(); ++i) {
        if (*(*i) == src) {
          delete *i;
          __list.erase(i);
          break;
        }
      }
    }
  }

private:
  std::vector<Entity *> __list;
};

} // namespace qtg

#endif /* end of include guard: __QTG_ENTITY_LIST_HPP__ */
