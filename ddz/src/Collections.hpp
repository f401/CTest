#ifndef __DDZ_COLLECTIONS_HPP__
#define __DDZ_COLLECTIONS_HPP__

#include "Card.hpp"
#include "defines.hpp"
#include <algorithm>
#include <cstdlib>
#include <vector>

namespace ddz {

class Player;

template <class T> class CommonCollections : public std::vector<T> {
public:
  using std::vector<T>::vector;
  using typename std::vector<T>::const_iterator;
  using typename std::vector<T>::iterator;

  void shuffle() noexcept {
    for (size_t i = 0; i < this->size(); ++i) {
      std::swap(this->at(i), this->at(rand() % this->size()));
    }
  }

  DDZ_INLINE void sort() noexcept {
    std::sort(this->begin(), this->end(),
              [](const T &a, const T &b) { return a.realNum > b.realNum; });
  }
};

using CardList = CommonCollections<Card>;
using PlayerList = CommonCollections<Player>;

} // namespace ddz

#endif /* CARDLIST_H */
