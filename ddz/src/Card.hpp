#ifndef __DDZ_CARD_HPP__

#define __DDZ_CARD_HPP__

#include "StringRef.hpp"
#include "defines.hpp"
#include "CardAttribute.hpp"
#include <algorithm>
#include <vector>

namespace ddz {

struct Card {
  CardAttribute flower;
  StringRef displayNum;
  real_num_t realNum;

  Card(CardAttribute flower, StringRef displayNum, real_num_t realNum)
      : flower(flower), displayNum(displayNum), realNum(realNum) {}

  DDZ_INLINE bool operator< (const Card& card) const noexcept { return realNum <  card.realNum; }
  DDZ_INLINE bool operator> (const Card& card) const noexcept { return realNum >  card.realNum; }
  DDZ_INLINE bool operator==(const Card& card) const noexcept { return realNum == card.realNum; }
};

} // namespace ddz
#endif /* end of include guard: __DDZ_CARD_HPP__ */
