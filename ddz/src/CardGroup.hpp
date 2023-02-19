#ifndef CARDGROUP_H
#define CARDGROUP_H

#include "CardType.hpp"

namespace ddz {

class CardGroup {
private:
  CardList list;
  CardType *type;
  CardGroup() : type(nullptr) {}

public:
  ~CardGroup() {
    if (type != nullptr)
      delete type;
  }

  DDZ_INLINE CardGroup(const CardGroup &src) : list(src.list) {
    type = src.type->copy();
  }

  DDZ_INLINE CardGroup(CardGroup &&src) : list(src.list) {
    type = src.type;
    src.type = nullptr;
  }

  DDZ_INLINE CardGroup &operator=(const CardGroup &src) {
    list = src.list;
    if (type != nullptr)
      delete type;
    type = src.type->copy();
    return *this;
  }

  DDZ_INLINE CardGroup &operator=(CardGroup &&src) {
    list = src.list;
    if (type != nullptr)
      delete type;
    type = src.type;
    src.type = nullptr;
    return *this;
  }

  DDZ_INLINE bool operator<(const CardGroup &other) const {
    return *type < *other.type;
  }
  DDZ_INLINE bool operator>(const CardGroup &other) const {
    return *type > *other.type;
  }
  static CardGroup whatType(CardList list);
};

} // namespace ddz

#endif /* CARDGROUP_H */
