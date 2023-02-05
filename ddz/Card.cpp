#include "Card.hpp"
#include "StringPool.hpp"
#include "StringRef.hpp"
#include <map>
#include <stdlib.h>

using namespace ddz::StringPool;

const static ddz::StringRef MAP[] = {THREE, FOUR, FIVE, SIX,   SEVEN,
                                     EIGHT, NINE, TEN,  J,     Q,
                                     K,     A,    TWO,  KING1, KING2};

const static std::map<ddz::StringRef, ddz::real_num_t> MAP_map = {
    {THREE, 0}, {FOUR, 1}, {FIVE, 2}, {SIX, 3},    {SEVEN, 4},
    {EIGHT, 5}, {NINE, 6}, {TEN, 7},  {J, 8},      {Q, 9},
    {K, 10},    {A, 11},   {TWO, 12}, {KING1, 13}, {KING2, 14}};

using namespace ddz;

StringRef ddz::getDisplayByReal(real_num_t src) { return MAP[src]; }

real_num_t ddz::getRealByDisplay(StringRef &ref) { return MAP_map.at(ref); }

CardList ddz::makeFullCardList() {
  CardList result = CardList();
  for (const auto &[key, value] : MAP_map) {
    result.push_back(Card(Flower::FangKuai, key, value));
    result.push_back(Card(Flower::HeiTao, key, value));
    result.push_back(Card(Flower::HongTao, key, value));
    result.push_back(Card(Flower::MeiHua, key, value));
  }
  return result;
}
