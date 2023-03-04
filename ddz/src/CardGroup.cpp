#include "CardGroup.hpp"
#include "CardRealNumPool.hpp"
#include "CardUtil.hpp"
#include "StringPool.hpp"
#include <cstdio>
#include <map>

using namespace ddz;

static DDZ_INLINE std::map<Card, size_t> cacCount(const CardList list) {
  std::map<Card, size_t> result = {};
  for (const auto &value : list) {
    result[value] = result[value] + 1;
  }
  return result;
}

CardGroup CardGroup::whatType(CardList list) {
  list.sort();
  auto countmap = cacCount(list);
  CardGroup result;
  result.list = list;
  
  // 统计最多卡以及最少卡
  size_t n = list.size();
  std::pair<const Card *, size_t> maxCnt, minCnt;
  for (const Card &card : list) {
    const size_t &current = countmap[card];
    if (current > maxCnt.second) {
      maxCnt.second = current;
      maxCnt.first = &card;
    }
    if (current < minCnt.second) {
      minCnt.second = current;
      minCnt.first = &card;
    }
  }

#define NEW_CARDTYPE(expr, what)                                               \
  if (expr) {                                                                  \
    result.type = new what;                                                    \
    return result;                                                             \
  }

  NEW_CARDTYPE(n == 1,
               CardType(CARD_WEIGHT_USUAL, CARD_TYPE_One, list.at(0))); // 单张
  NEW_CARDTYPE(
      n == 2 && maxCnt.second == 2,
      CardType(CARD_WEIGHT_USUAL, CARD_TYPE_DuiZi, list.at(0))); // 对子
  NEW_CARDTYPE(
      n == 2 && maxCnt.second == 1 && minCnt.second == 1 &&
          list.at(0).realNum == REAL_NUM_KING1 &&
          list.at(1).realNum == REAL_NUM_KING2,
      CardType(CARD_WEIGHT_KING_BOOM, CARD_TYPE_WangZha, list.at(0))); // 王炸
  NEW_CARDTYPE(
      n == 3 && maxCnt.second == 3,
      CardType(CARD_WEIGHT_USUAL, CARD_TYPE_Three, list.at(0))); // 三张
  NEW_CARDTYPE(n == 4 && maxCnt.second == 3,
               CardType(CARD_WEIGHT_USUAL, CARD_TYPE_ThreeWithOne,
                        *maxCnt.first)) // 三带一
  NEW_CARDTYPE(n == 5 && maxCnt.second == 3 && minCnt.second == 2,
               CardType(CARD_WEIGHT_USUAL, CARD_TYPE_ThreeWithTwo,
                        *maxCnt.first)) // 三带一对
  NEW_CARDTYPE(n == 4 && maxCnt.second == 4,
               CardType(CARD_WEIGHT_BOOM, CARD_TYPE_BOOM, list.at(0))); // 炸弹
  NEW_CARDTYPE(n == 6 && maxCnt.second == 4,
               CardType(CARD_WEIGHT_USUAL, CARD_TYPE_FourWithOne,
                        *maxCnt.first)); // 四带二
  NEW_CARDTYPE(n == 8 && maxCnt.second == 4 && minCnt.second == 2,
               CardType(CARD_WEIGHT_USUAL, CARD_TYPE_FourWithTwo,
                        *maxCnt.first)); // 四带二对
  NEW_CARDTYPE(
      n >= 5 && maxCnt.second == 1 &&
          list[0].realNum + n - 1 == list.end()->realNum,
      CardType(CARD_WEIGHT_USUAL, CARD_TYPE_ShunZi, *list.end())); // 顺子
  NEW_CARDTYPE(
      n >= 6 && maxCnt.second == 2 && minCnt.second == 2 &&
          list[0].realNum == list[n - 1].realNum + n / 2 - 1,
      CardType(CARD_WEIGHT_USUAL, CARD_TYPE_LianDui, *list.end())); // 连对

  size_t cntCount = 1;
  {
    real_num_t prev = 32767;
    for (const auto &[key, value] : countmap) {
      if (value >= 3) {
        if (prev == 32767) {
          prev = key.realNum;
          continue;
        }
        if (prev == key.realNum - 1)
          ++cntCount;
        prev = key.realNum;
      }
    }
  }

  if (cntCount > 1) {
    NEW_CARDTYPE(n == cntCount * 3 || (n == cntCount * 3 + cntCount) ||
                     (minCnt.second == 2 && n == cntCount * 3 + cntCount * 2),
                 CardType(CARD_WEIGHT_USUAL, CARD_TYPE_FeiJi, *maxCnt.first));
  }
  fprintf(stderr, "Unknow CardType ");
  return result;
}
