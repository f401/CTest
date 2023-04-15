#ifndef CARDGROUP_H
#define CARDGROUP_H

#include "CardType.hpp"
#include "Collections.hpp"

namespace ddz {

class CardGroup {
private:
  CardList list;
  CardType *type;
  CardGroup() : type(nullptr) {}

public:
  ~CardGroup() noexcept { delete type; }

  DDZ_FORCE_INLINE CardGroup(const CardGroup &src) : list(src.list) {
    type = src.type->copy();
  }

  DDZ_FORCE_INLINE CardGroup(CardGroup &&src) : list(src.list) {
    type = src.type;
    src.type = nullptr;
  }

  DDZ_FORCE_INLINE CardGroup &operator=(const CardGroup &src) {
    if (&src != this) {
      delete type;
      list = src.list;
      type = src.type->copy();
    }
    return *this;
  }

  DDZ_INLINE CardGroup &operator=(CardGroup &&src) {
    if (&src != this) {
      delete type;
      list = src.list;
      type = src.type;
      src.type = nullptr;
    }
    return *this;
  }

  DDZ_FORCE_INLINE bool operator<(const CardGroup &other) const {
    return *type < *other.type;
  }
  DDZ_FORCE_INLINE bool operator>(const CardGroup &other) const {
    return *type > *other.type;
  }

  static CardGroup whatType(CardList list);

  DDZ_NO_DISCARD DDZ_FORCE_INLINE CardType &cardType() noexcept {
    return *type;
  }
};

} // namespace ddz

#endif /* CARDGROUP_H */
