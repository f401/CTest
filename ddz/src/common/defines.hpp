#ifndef __DDZ_DEFINES_H__

#define __DDZ_DEFINES_H__

namespace ddz {

class StringRef;

typedef unsigned short real_num_t;

typedef float weight_t;
typedef int card_type_t;

typedef StringRef display_str_t;

#define DDZ_INLINE inline
#define DDZ_FORCE_INLINE __attribute__((always_inline)) DDZ_INLINE

#define DDZ_NO_DISCARD [[nodiscard]]
#define DDZ_CONSTEXPR constexpr

#define DDZ_INLINE_CONSTEXPR DDZ_INLINE DDZ_CONSTEXPR
#define DDZ_NO_DISCARD_INLINE_CONSTEXPR DDZ_NO_DISCARD DDZ_INLINE DDZ_CONSTEXPR



#define DDZ_USE_STL_SHUFFLE
#define DDZ_SEND_CARDS_USE_RANGE

}
#endif /* end of include guard: __DDZ_DEFINES_H__ */
