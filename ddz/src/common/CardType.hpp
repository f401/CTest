#ifndef __DDZ_CARDTYPE_HPP__
#define __DDZ_CARDTYPE_HPP__

#include "Card.hpp"
#include "utils/Collections.hpp"
#include "pools/CardTypeWeightPool.h"

namespace ddz {

class CardType {
protected:
  weight_t weight;
  card_type_t type;
  Card insteadOf; // 一种方式比较两个类型的大小

public:
  DDZ_INLINE_CONSTEXPR CardType(weight_t weight, card_type_t type, Card min)
      : weight(weight), type(type), insteadOf(min) {}

  virtual ~CardType() {}

  virtual bool operator>(const CardType &other) const noexcept {
    if (weight > other.weight)
      return true;
    else if (weight == other.weight && type == other.type)
      return insteadOf > other.insteadOf;
    return false;
  }
  virtual bool operator<(const CardType &other) const noexcept {
    if (weight < other.weight)
      return true;
    else if (weight == other.weight && type == other.type)
      return insteadOf < other.insteadOf;
    return false;
  }

  virtual CardType *copy() const { return new CardType(*this); }

  DDZ_NO_DISCARD DDZ_FORCE_INLINE weight_t getWeight() const noexcept {
    return weight;
  }

  DDZ_NO_DISCARD DDZ_FORCE_INLINE card_type_t getCardType() const noexcept {
    return type;
  }
};

} // namespace ddz

#endif /* CARDTYPE_H */
