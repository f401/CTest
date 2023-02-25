#ifndef __DDZ_COLLECTIONS_HPP__
#define __DDZ_COLLECTIONS_HPP__

#include "Card.hpp"
#include "defines.hpp"
#include <algorithm>
#include <cstdlib>
#include <vector>

namespace ddz {

class Player;

template <class T>
class CommonCollections : public std::vector<T> {
public:
  using std::vector<T>::vector;

  void shuffle() {
    for (size_t i = 0; i < this->size(); ++i) {
      std::swap(this->at(i), this->at(rand() % this->size()));
    }
  }

  DDZ_INLINE void sort() {
    std::sort(this->begin(), this->end(), [](const T &a, const T &b) {
      return a.realNum > b.realNum;
    });
  }

  DDZ_INLINE void moveTo(CommonCollections& other, size_t start, size_t count) {
    while(count--)
    	other.push_back(this->at(start + count));
  }
};

using CardList = CommonCollections<Card>;
using PlayerList = CommonCollections<Player>;

} // namespace ddz

#endif /* CARDLIST_H */
