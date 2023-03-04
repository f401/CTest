#ifndef __DDZ_CARD_UTILS_HPP__
#define __DDZ_CARD_UTILS_HPP__

#include "Collections.hpp"
#include "Player.hpp"
#include "StringRef.hpp"

namespace ddz {
extern inline StringRef getDisplayByReal(real_num_t src)
    __attribute__((always_inline, const));
extern inline real_num_t getRealByDisplay(StringRef &ref)
    __attribute__((always_inline, const));
CardList makeFullCardList();
PlayerList &sendCardToEachPlayer(PlayerList &list, CardList &&cards) noexcept;
PlayerList &sendCardToEachPlayer(PlayerList &list,
                                 const CardList &cards) noexcept;

} // namespace ddz

#endif /* end of include guard: __DDZ_CARD_UTILS_HPP__ */
