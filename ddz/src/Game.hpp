#ifndef GAME_H
#define GAME_H

// TODO: FINISH

#include "CardGroup.hpp"
#include "CardStack.hpp"
#include "CardUtil.hpp"
#include "Player.hpp"

namespace ddz {

class Game {
private:
  PlayerList players;
  CardStack stack;

  CardList diPai;

public:
  Game(PlayerList players) : players(players) {
    CardList cards = this->makeFullCardList();
    cards.moveTo(diPai, 0, 3);
  }
  virtual CardList makeFullCardList() { return ddz::makeFullCardList(); }

  virtual void sendCardToEachPlayer(CardList &cards) {
    ddz::sendCardToEachPlayer(players, cards);
  }

  virtual void selectLandOwner() {}

  DDZ_INLINE void sendCardToLandOwner() {
    diPai.moveTo(players[0].cards(), 0, 3);
  }

  void startGame() {
    selectLandOwner();
    sendCardToLandOwner();
    size_t currentTurn = 0;
    for (;;) {

      if (++currentTurn == 4) {
        currentTurn = 0;
      }
    }
  }
};

} // namespace ddz

#endif /* GAME_H */
