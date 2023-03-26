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
  using std::vector<T>::size;
  using std::vector<T>::at;
  using std::vector<T>::begin;

  void shuffle() noexcept {
    for (size_t i = 0; i < this->size(); ++i) {
      std::swap(at(i), at(rand() % size()));
    }
  }

  DDZ_INLINE void sort() noexcept {
    std::sort(this->begin(), this->end(),
              [](const T &a, const T &b) { return a.realNum > b.realNum; });
  }

  DDZ_NO_DISCARD_INLINE_CONSTEXPR bool isEmpty() const noexcept {
    return size() == 0;
  }

  void moveTo(CommonCollections &other, size_t start, size_t count) {
    auto thisBegin = this->begin() + start, thisEnd = thisBegin + count;
    if constexpr (std::is_move_constructible_v<T>) {
      other.insert(other.end(), std::make_move_iterator(thisBegin),
                   std::make_move_iterator(thisEnd));
    } else {
      other.insert(other.end(), thisBegin, thisEnd);
    }
    this->erase(thisBegin, thisEnd);
  }
};

using CardList = CommonCollections<Card>;
using PlayerList = CommonCollections<Player>;

} // namespace ddz

#endif /* CARDLIST_H */
