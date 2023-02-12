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
};

class CardList : public std::vector<struct Card> {
public:
  void shuffle() {
    for (size_t i = 0; i < size(); ++i) {
      std::swap(at(i), at(rand() % size()));
    }
  }

  DDZ_INLINE void sort() {
	  std::sort(begin(), end(), [](const Card &a, const Card &b) { return a.realNum > b.realNum; }); 
  }
};

extern inline StringRef getDisplayByReal(real_num_t src) __attribute__((always_inline, const));

extern inline real_num_t getRealByDisplay(StringRef &ref) __attribute__((always_inline, const));

CardList makeFullCardList();

} // namespace ddz
#endif /* end of include guard: __DDZ_CARD_HPP__ */
