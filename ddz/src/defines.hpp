#ifndef __DDZ_DEFINES_H__

#define __DDZ_DEFINES_H__

namespace ddz {

class StringRef;

typedef unsigned short real_num_t;
typedef StringRef display_str_t;

#define DDZ_INLINE __attribute__((always_inline)) inline

#define DDZ_STRINGPOOL_USE_INLINE

}
#endif /* end of include guard: __DDZ_DEFINES_H__ */
