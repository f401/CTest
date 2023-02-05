#ifndef __DDZ_CARD_HPP__

#define __DDZ_CARD_HPP__

#include "StringRef.hpp"
#include "defines.hpp"
#include <algorithm>
#include <vector>

namespace ddz {

#define FLOWER_COLOR_BLACK 0
#define FLOWER_COLOR_RED 1

enum class Flower {
  HongTao = FLOWER_COLOR_RED,
  MeiHua = FLOWER_COLOR_BLACK,
  HeiTao = FLOWER_COLOR_BLACK,
  FangKuai = FLOWER_COLOR_RED
};

struct Card {
  Flower flower;
  StringRef displayNum;
  real_num_t realNum;

  Card(Flower flower, StringRef displayNum, real_num_t realNum)
      : flower(flower), displayNum(displayNum), realNum(realNum) {}
};

class CardList : public std::vector<struct Card> {
public:
  void shuffle() {
    for (int i = 0; i < size(); ++i) {
      std::swap(at(i), at(rand() % size()));
    }
  }
};

extern inline StringRef getDisplayByReal(real_num_t src) __attribute__((always_inline, const));

extern inline real_num_t getRealByDisplay(StringRef &ref) __attribute__((always_inline, const));

CardList makeFullCardList();

} // namespace ddz
#endif /* end of include guard: __DDZ_CARD_HPP__ */
