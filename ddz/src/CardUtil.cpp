#include "CardUtil.hpp"
#include "Card.hpp"
#include "StringPool.hpp"
#include "StringRef.hpp"
#include <map>
#include <stdlib.h>

using namespace ddz::StringPool;

const static ddz::StringRef MAP[] = {THREE,   FOUR, FIVE,  SIX,  SEVEN, EIGHT,
                                     NINE,    TEN,  J,     Q,    K,     A,
                                     nullptr, TWO,  KING1, KING2};

const static std::map<ddz::StringRef, ddz::real_num_t> MAP_map = {
    {THREE, 0}, {FOUR, 1}, {FIVE, 2}, {SIX, 3},    {SEVEN, 4},
    {EIGHT, 5}, {NINE, 6}, {TEN, 7},  {J, 8},      {Q, 9},
    {K, 10},    {A, 11},   {TWO, 13}, {KING1, 14}, {KING2, 15}};

using namespace ddz;

StringRef ddz::getDisplayByReal(real_num_t src) { return MAP[src]; }

real_num_t ddz::getRealByDisplay(StringRef &ref) { return MAP_map.at(ref); }

CardList ddz::makeFullCardList() {
  CardList result = CardList();
  for (const auto &[key, value] : MAP_map) {
    if (key == KING1) {
      result.push_back(Card(CardAttributes::KING1, key, value));
    } else if (key == KING2) {
      result.push_back(Card(CardAttributes::KING2, key, value));
    } else {
      result.push_back(Card(CardAttributes::FangKuai, key, value));
      result.push_back(Card(CardAttributes::HeiTao, key, value));
      result.push_back(Card(CardAttributes::HongTao, key, value));
      result.push_back(Card(CardAttributes::MeiHua, key, value));
    }
  }
  return result;
}

PlayerList &ddz::sendCardToEachPlayer(PlayerList &list,
                                      const CardList &cards) noexcept {
  for (size_t i = 0, players = list.size(); i < cards.size(); ++i) {
    list[i % players].cards().push_back(cards[i]);
  }
  return list;
}

PlayerList &ddz::sendCardToEachPlayer(PlayerList &list,
                                      CardList &&cards) noexcept {
  for (size_t players = list.size(), i = 0; i < cards.size(); ++i) {
    list[i % players].cards().push_back(std::move(cards[i]));
  }
  return list;
}
