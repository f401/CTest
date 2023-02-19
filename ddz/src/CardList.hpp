#ifndef CARDLIST_H
#define CARDLIST_H

#include "Card.hpp"
#include "defines.hpp"
#include <algorithm>
#include <cstdlib>
#include <vector>

namespace ddz {

class CardList : public std::vector<Card> {
public:
  using std::vector<Card>::vector;
  void shuffle() {
    for (size_t i = 0; i < size(); ++i) {
      std::swap(at(i), at(rand() % size()));
    }
  }

  DDZ_INLINE void sort() {
    std::sort(begin(), end(), [](const Card &a, const Card &b) {
      return a.realNum > b.realNum;
    });
  }

  DDZ_INLINE void moveTo(CardList& other, size_t start, size_t count) {
    while(count--)
    	other.push_back(at(start + count));
  }
};


} // namespace ddz

#endif /* CARDLIST_H */
