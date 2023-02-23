#ifndef MAP_H
#define MAP_H

#include <string.h>

typedef struct map_node_t map_node_t;

typedef struct {
	map_node_t **buckets;
	unsigned nbuckets, nnodes;
} map_base_t;

typedef struct {
	unsigned bucketidx;
	map_node_t *node;
} map_iter_t;

#define map_t(type) \
	struct { map_base_t base; type *ref; type tmp; }

#define map_init(m) \
	memset(m, 0, sizeof(*(m)))

#define map_deinit(m) \
	___map_deinit(&(m)->base)

#define map_get(m, key) \
	((m)->ref = ___map_get(&(m)->base, key))

#define map_set(m, key, val)	 \
	((m)->tmp = (val),	 \
	___map_set(&(m)->base, key, &(m)->tmp, sizeof((m)->tmp)))

#define map_remove(m, key) \
	___map_remove(&(m)->base, key)

#define map_iter(m) \
	___map_iter()

#define map_next(m, iter) \
	___map_next(&(m)->base, iter)

void ___map_deinit(map_base_t *m);
void *___map_get(map_base_t *m, const char *key);
int ___map_set(map_base_t *m, const char *key, void *val, int vsize);
void ___map_remove(map_base_t *m, const char *key);
map_iter_t ___map_iter();
const char *___map_next(map_base_t *m, map_iter_t *iter);

#endif /* MAP_H */
