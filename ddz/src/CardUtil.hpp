#ifndef __DDZ_CARD_UTILS_HPP__
#define __DDZ_CARD_UTILS_HPP__

#include "StringRef.hpp"
#include "Player.hpp"
#include "Collections.hpp"

namespace ddz {
extern inline StringRef getDisplayByReal(real_num_t src) __attribute__((always_inline, const));
extern inline real_num_t getRealByDisplay(StringRef &ref) __attribute__((always_inline, const));
CardList makeFullCardList();
PlayerList& sendCardToEachPlayer(PlayerList &list, CardList cards, bool shuffle = true);
}

#endif /* end of include guard: __DDZ_CARD_UTILS_HPP__ */
