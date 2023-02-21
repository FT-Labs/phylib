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

#define BETWEEN(x, a, b)    ((a) <= (x) && (x) <= (b))
#define LEN(x) sizeof(x)/sizeof(x[0])

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

typedef struct llist_t {
	struct llist_t *link;
	char *data;
} llist_t;
void llist_add_to(llist_t **old_head, void *data);
void llist_add_to_end(llist_t **list_head, void *data);
void *llist_pop(llist_t **elm);
void llist_unlink(llist_t **head, llist_t *elm);
void llist_free(llist_t *elm, void (*freeit)(void *data));
llist_t *llist_rev(llist_t *list);
llist_t *llist_find_str(llist_t *first, const char *str);

typedef uint_least32_t Rune;
size_t utf8encode(Rune, char *);
char utf8encodebyte(Rune, size_t);
size_t utf8validate(Rune *, size_t);
Rune utf8decodebyte(char c, size_t *i);




#endif /* LIBPHY_H */
