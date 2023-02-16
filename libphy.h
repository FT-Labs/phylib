#ifndef LIBPHY_H
#define LIBPHY_H 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <locale.h>
#include <errno.h>
#include <ctype.h>

#include <time.h>
typedef double duration_t;
void sleep_for_duration(duration_t duration);
duration_t parse_duration_str(char *str);

struct suffix_mult {
	char suffix[4];
	uint32_t mult;
};

#define UNUSED_PARAM __attribute__((__unused__))
#define NORETURN __attribute__((__noreturn__))
#define RETURNS_MALLOC __attribute__((malloc))
#define ALIGNED(m) __attribute__((__aligned__(m)))
#define ALWAYS_INLINE __attribute__((always_inline)) inline
#define UNUSED_PARAM_RESULT __attribute__((warn_unused_result))

/* Endian */
#include <limits.h>
#include <byteswap.h>
#include <endian.h>

#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN
#define PHY_BIG_ENDIAN 1
#define PHY_LITTLE_ENDIAN 0
#elif defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN
#define PHY_BIG_ENDIAN 0
#define PHY_LITTLE_ENDIAN 1
#endif

#define ALIGN1 __attribute__((aligned(1)))
#define ALIGN2 __attribute__((aligned(2)))
#define ALIGN4 __attribute__((aligned(4)))
#define ALIGN8 __attribute__((aligned(8)))
#define ALIGN_INT __attribute__((aligned(sizeof(int))))
#define ALIGN_PTR __attribute__((aligned(sizeof(void *))))
#define ALIGN_SUFFIX ALIGN4
extern const struct suffix_mult bkm_suffixes[];
#define km_suffixes (bkm_suffixes + 1)
extern const struct suffix_mult cwbkMG_suffixes[];
#define kMG_suffixes (cwbkMG_suffixes + 3)
extern const struct suffix_mult kmg_i_suffixes[];
#include "xatonum.h"

#endif /* LIBPHY_H */
