#ifndef __DDZ_CARD_HPP__

#define __DDZ_CARD_HPP__

#include "CardAttribute.hpp"
#include "StringRef.hpp"
#include "defines.hpp"
#include <algorithm>
#include <vector>

namespace ddz {

struct Card {
  CardAttribute flower;
  StringRef displayNum;
  real_num_t realNum;

  DDZ_INLINE_CONSTEXPR Card(CardAttribute flower, StringRef displayNum,
                            real_num_t realNum)
      : flower(flower), displayNum(displayNum), realNum(realNum) {}

  DDZ_INLINE_CONSTEXPR bool operator<(const Card &card) const noexcept {
    return realNum < card.realNum;
  }

  DDZ_INLINE_CONSTEXPR bool operator>(const Card &card) const noexcept {
    return realNum > card.realNum;
  }

  DDZ_INLINE_CONSTEXPR bool operator==(const Card &card) const noexcept {
    return realNum == card.realNum;
  }
};

DDZ_INLINE std::ostream &operator<<(std::ostream &stream, const Card &card) noexcept {
  std::cout << card.realNum << std::endl;
  return stream;
}

} // namespace ddz

#endif /* end of include guard: __DDZ_CARD_HPP__ */
