#ifndef __DDZ_CARDTYPE_HPP__
#define __DDZ_CARDTYPE_HPP__

#include "Card.hpp"
#include "Collections.hpp"

namespace ddz {

#define CARD_WEIGHT_USUAL 0
#define CARD_WEIGHT_BOOM 1
#define CARD_WEIGHT_KING_BOOM 2

#define CARD_TYPE_One 0
#define CARD_TYPE_DuiZi 1
#define CARD_TYPE_Three 3
#define CARD_TYPE_ThreeWithOne 4
#define CARD_TYPE_ThreeWithTwo 5
#define CARD_TYPE_BOOM 5
#define CARD_TYPE_FourWithOne 6
#define CARD_TYPE_FourWithTwo 7
#define CARD_TYPE_ShunZi 8
#define CARD_TYPE_LianDui 9
#define CARD_TYPE_FeiJi 10
#define CARD_TYPE_WangZha 11

class CardType {
protected:
  weight_t weight;
  card_type_t type;
  Card insteadOf;

public:
  CardType(weight_t weight, card_type_t type, Card min)
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
};

} // namespace ddz

#endif /* CARDTYPE_H */
