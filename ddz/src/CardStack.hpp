#ifndef CARDSTACK_H
#define CARDSTACK_H

#include "CardGroup.hpp"
#include "Player.hpp"

namespace ddz {

class CardStack {
private:
  CardGroup *top;
  Player *owner;

public:
  CardStack(Player *owner = nullptr, CardGroup *group = nullptr)
      : owner(owner) {
    top = group == nullptr ? nullptr : new CardGroup(*group);
  }
  ~CardStack() {
    if (top != nullptr)
      delete top;
  }

  DDZ_INLINE void reset(Player *owner, CardGroup *newer) {
    if (top != nullptr)
      delete top;
    this->owner = owner;
    this->top = new CardGroup(*newer);
  }

  DDZ_FORCE_INLINE bool is_top_player(Player &other) { return *owner == other; }

  bool push(Player *owner, CardGroup *newer) {
    if (*top < *newer) {
      if (top != nullptr) {
        delete top;
      }
      this->owner = owner;
      this->top = new CardGroup(*newer);
      return true;
    }
    return false;
  }
};

} // namespace ddz

#endif /* CARDSTACK_H */
