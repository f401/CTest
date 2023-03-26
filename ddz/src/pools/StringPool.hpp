#ifndef __DDZ_STRING_POOL_HPP__

#define __DDZ_STRING_POOL_HPP__

namespace ddz::StringPool {
#ifndef DE_VAR
#  define DE_VAR inline constexpr 
#endif
DE_VAR const char* THREE = "3";
DE_VAR const char* FOUR = "4";
DE_VAR const char* FIVE = "5";
DE_VAR const char* SIX = "6";
DE_VAR const char* SEVEN = "7";
DE_VAR const char* EIGHT = "8";
DE_VAR const char* NINE = "9";
DE_VAR const char* TEN = "10";
DE_VAR const char* J = "J";
DE_VAR const char* Q = "Q";
DE_VAR const char* K = "K";
DE_VAR const char* A = "A";
DE_VAR const char* TWO = "2";
DE_VAR const char* KING1 = "KING1";
DE_VAR const char* KING2 = "KING2";
#undef DE_VAR
}

#endif /* end of include guard: __DDZ_STRING_POOL_HPP__ */
