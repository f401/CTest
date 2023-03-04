#include <iostream>

#include "Card.hpp"
#include "CardGroup.hpp"
#include "CardUtil.hpp"
#include "StringPool.hpp"

__attribute__((constructor(101))) void makeRandSeed() { srand(time(0)); }

void testCardList() {
  ddz::CardList list = ddz::makeFullCardList();
  list.shuffle();
  list.sort();
  for (ddz::Card card : list) {
    std::cout << "displayNum: " << card.displayNum.cppStr()
              << ", Real: " << card.realNum << std::endl;
  }
  std::cout << list.size() << std::endl;
}

void testCardType() {
  using namespace ddz;
  Card three(CardAttributes::FangKuai, StringPool::THREE, 0);
  Card four(CardAttributes::FangKuai, StringPool::FOUR, 1);
  Card five(CardAttributes::FangKuai, StringPool::FIVE, 2);
  CardList list = {three, three, three, four, four, four, five, five, five};
  CardGroup::whatType(list);
}

void testSendCard() {
  using namespace ddz;
  PlayerList list = {Player(), Player(), Player()};
  CardList fullCard = makeFullCardList();
  sendCardToEachPlayer(list, std::move(fullCard));
  using namespace std;
  for (auto i = list.begin(); i != list.end(); ++i) {
    cout << "Player:" << endl;
    i->cards().sort();
    for (auto j = i->cards().begin(); j != i->cards().end(); ++j) {
      cout << j->displayNum << endl;
    }
    cout << endl;
  }
}

int main(int argc, char *argv[]) {
	testSendCard();
	return 0; 
}
