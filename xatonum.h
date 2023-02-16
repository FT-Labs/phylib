/* Provides extern declarations of functions */
#define DECLARE_STR_CONV(type, T, UT) \
\
unsigned type xstrto##UT##_range_sfx(const char *str, int b, unsigned type l, unsigned type u, const struct suffix_mult *sfx) ; \
unsigned type xstrto##UT##_range(const char *str, int b, unsigned type l, unsigned type u) ; \
unsigned type xstrto##UT##_sfx(const char *str, int b, const struct suffix_mult *sfx) ; \
unsigned type xstrto##UT(const char *str, int b) ; \
unsigned type xato##UT##_range_sfx(const char *str, unsigned type l, unsigned type u, const struct suffix_mult *sfx) ; \
unsigned type xato##UT##_range(const char *str, unsigned type l, unsigned type u) ; \
unsigned type xato##UT##_sfx(const char *str, const struct suffix_mult *sfx) ; \
unsigned type xato##UT(const char *str) ; \
type xstrto##T##_range_sfx(const char *str, int b, type l, type u, const struct suffix_mult *sfx) ; \
type xstrto##T##_range(const char *str, int b, type l, type u) ; \
type xstrto##T(const char *str, int b) ; \
type xato##T##_range_sfx(const char *str, type l, type u, const struct suffix_mult *sfx) ; \
type xato##T##_range(const char *str, type l, type u) ; \
type xato##T##_sfx(const char *str, const struct suffix_mult *sfx) ; \
type xato##T(const char *str) ; \

/* Provides inline definitions of functions */
/* (useful for mapping them to the type of the same width) */
#define DEFINE_EQUIV_STR_CONV(narrow, N, W, UN, UW) \
\
static ALWAYS_INLINE \
unsigned narrow xstrto##UN##_range_sfx(const char *str, int b, unsigned narrow l, unsigned narrow u, const struct suffix_mult *sfx) \
{ return xstrto##UW##_range_sfx(str, b, l, u, sfx); } \
static ALWAYS_INLINE \
unsigned narrow xstrto##UN##_range(const char *str, int b, unsigned narrow l, unsigned narrow u) \
{ return xstrto##UW##_range(str, b, l, u); } \
static ALWAYS_INLINE \
unsigned narrow xstrto##UN##_sfx(const char *str, int b, const struct suffix_mult *sfx) \
{ return xstrto##UW##_sfx(str, b, sfx); } \
static ALWAYS_INLINE \
unsigned narrow xstrto##UN(const char *str, int b) \
{ return xstrto##UW(str, b); } \
static ALWAYS_INLINE \
unsigned narrow xato##UN##_range_sfx(const char *str, unsigned narrow l, unsigned narrow u, const struct suffix_mult *sfx) \
{ return xato##UW##_range_sfx(str, l, u, sfx); } \
static ALWAYS_INLINE \
unsigned narrow xato##UN##_range(const char *str, unsigned narrow l, unsigned narrow u) \
{ return xato##UW##_range(str, l, u); } \
static ALWAYS_INLINE \
unsigned narrow xato##UN##_sfx(const char *str, const struct suffix_mult *sfx) \
{ return xato##UW##_sfx(str, sfx); } \
static ALWAYS_INLINE \
unsigned narrow xato##UN(const char *str) \
{ return xato##UW(str); } \
static ALWAYS_INLINE \
narrow xstrto##N##_range_sfx(const char *str, int b, narrow l, narrow u, const struct suffix_mult *sfx) \
{ return xstrto##W##_range_sfx(str, b, l, u, sfx); } \
static ALWAYS_INLINE \
narrow xstrto##N##_range(const char *str, int b, narrow l, narrow u) \
{ return xstrto##W##_range(str, b, l, u); } \
static ALWAYS_INLINE \
narrow xstrto##N(const char *str, int b) \
{ return xstrto##W(str, b); } \
static ALWAYS_INLINE \
narrow xato##N##_range_sfx(const char *str, narrow l, narrow u, const struct suffix_mult *sfx) \
{ return xato##W##_range_sfx(str, l, u, sfx); } \
static ALWAYS_INLINE \
narrow xato##N##_range(const char *str, narrow l, narrow u) \
{ return xato##W##_range(str, l, u); } \
static ALWAYS_INLINE \
narrow xato##N##_sfx(const char *str, const struct suffix_mult *sfx) \
{ return xato##W##_sfx(str, sfx); } \
static ALWAYS_INLINE \
narrow xato##N(const char *str) \
{ return xato##W(str); }
