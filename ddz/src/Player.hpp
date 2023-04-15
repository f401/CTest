#ifndef PLAYER_H
#define PLAYER_H

#include "Collections.hpp"
#include <vector>

namespace ddz {
typedef int player_id_t;

class Player {
protected:
  CardList haveCards;
  player_id_t id;

public:
  Player() : haveCards() {}

  DDZ_FORCE_INLINE CardList &cards() { return haveCards; }
  DDZ_FORCE_INLINE bool operator==(const Player &other) noexcept { return id == other.id; }
};
} // namespace ddz

#endif /* PLAYER_H */
