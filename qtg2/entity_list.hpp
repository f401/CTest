#ifndef __QTG_ENTITY_LIST_HPP__

#define __QTG_ENTITY_LIST_HPP__

#include "entity.hpp"
#include <algorithm>
#include <vector>

namespace qtg {

class EntityList {
public:
  EntityList() : __list() {}

  ~EntityList() { __release_ptrs(); }

  typedef std::vector<Entity *>::iterator iterator;
  typedef std::vector<Entity *>::const_iterator const_iterator;

  QTG_INLINE iterator begin() noexcept { return __list.begin(); }
  QTG_INLINE iterator end() noexcept { return __list.end(); }
  QTG_INLINE const_iterator cbegin() const noexcept { return __list.cbegin(); }
  QTG_INLINE const_iterator cend() const noexcept { return __list.cend(); }

  EntityList(const EntityList &src) : EntityList() {
    for (auto i = src.cbegin(); i != src.cend(); ++i) {
      __list.push_back((*i)->copy());
    }
  }

  EntityList(EntityList &&src) = default;
  EntityList &operator=(const EntityList &src) {
    __release_ptrs();
    for (auto i = src.cbegin(); i != src.cend(); ++i) {
      __list.push_back((*i)->copy());
    }
    return *this;
  }
  EntityList &operator=(EntityList &&src) = default;

  QTG_INLINE Entity &get(size_t idx) const noexcept { return *__list[idx]; }

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

  QTG_INLINE Entity &operator[](const size_t idx) const noexcept {
    return *__list[idx];
  }

private:
  QTG_INLINE void __release_ptrs() {
    for (auto i : __list) {
      delete i;
    }
  }

  std::vector<Entity *> __list;
};

} // namespace qtg

#endif /* end of include guard: __QTG_ENTITY_LIST_HPP__ */
