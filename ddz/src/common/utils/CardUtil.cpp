#include "CardUtil.hpp"
#include "Card.hpp"
#include "StringRef.hpp"
#include "pools/CardRealNumPool.h"
#include "pools/StringPool.hpp"
#include <iostream>
#include <map>
#include <stdlib.h>

using namespace ddz::StringPool;

const static ddz::StringRef MAP[] = {
    THREE, FOUR, FIVE, SIX, SEVEN,   EIGHT, NINE,  TEN,
    J,     Q,    K,    A,   "EMPTY", TWO,   KING1, KING2};

const static std::map<ddz::StringRef, ddz::real_num_t> MAP_map = {
    {THREE, REAL_NUM_THREE}, {FOUR, REAL_NUM_FOUR},   {FIVE, REAL_NUM_FIVE},
    {SIX, REAL_NUM_SIX},     {SEVEN, REAL_NUM_SEVEN}, {EIGHT, REAL_NUM_EIGHT},
    {NINE, REAL_NUM_NINE},   {TEN, REAL_NUM_TEN},     {J, REAL_NUM_J},
    {Q, REAL_NUM_Q},         {K, REAL_NUM_K},         {A, REAL_NUM_A},
    {TWO, REAL_NUM_TWO},     {KING1, REAL_NUM_KING1}, {KING2, REAL_NUM_KING2}};

using namespace ddz;

StringRef ddz::getDisplayByReal(real_num_t src) noexcept {
  return MAP[src];
}

real_num_t ddz::getRealByDisplay(const StringRef &ref) noexcept {
  return MAP_map.at(ref);
}

CardList ddz::makeFullCardList() noexcept {
  CardList result = CardList();
  for (const auto &[key, value] : MAP_map) {
    if (value == REAL_NUM_KING1) {
      result.push_back(Card(CardAttributes::KING1, key, value));
    } else if (value == REAL_NUM_KING2) {
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
#ifdef DDZ_SEND_CARDS_USE_RANGE
  if (cards.size() % list.size() != 0) {
    std::cerr << "玩家数量与牌数无法达到平均" << std::endl;
  }
  size_t aPlayerCardCount = cards.size() / list.size();
  for (auto i = list.begin(); i != list.end(); ++i) {
    cards.moveTo(i->cards(), 0, aPlayerCardCount);
  }
#else
  for (size_t players = list.size(), i = 0; i < cards.size(); ++i) {
    list[i % players].cards().push_back(std::move(cards[i]));
    std::cout << i << std::endl;
  }
  cards.clear();
#endif
  return list;
}
