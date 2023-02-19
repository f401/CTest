#ifndef PLAYER_H
#define PLAYER_H

#include "CardList.hpp"
#include <vector>

namespace ddz {
typedef int player_id_t;

class Player {
protected:
  CardList haveCards;
  player_id_t id;

public:
  Player() : haveCards() {}

  DDZ_INLINE CardList &cards() { return haveCards; }
  DDZ_INLINE bool operator==(const Player &other) { return id == other.id; }
};

typedef std::vector<Player> PlayerList;
} // namespace ddz

#endif /* PLAYER_H */
