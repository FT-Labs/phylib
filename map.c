#include <stdlib.h>
#include <string.h>
#include "map.h"


struct map_node_t {
	unsigned hash;
	void *val;
	map_node_t *next;
};

static unsigned
map_hash(const char *str)
{
	if (!str)
		return 0;
	unsigned hash = 5381;
	while (*str)
		hash = ((hash << 5) + hash) ^ *str++;
	return hash;
}

static map_node_t *
map_newnode(const char *key, void *val, int vsize)
{
	int ksize = strlen(key) + 1;
	int voffset = ksize + ((sizeof(void *) - ksize) % sizeof(void *));
	map_node_t *node = malloc(sizeof(map_node_t) + voffset + vsize);
	if (!node) return NULL;
	memcpy(node + 1, key, ksize);
	node->hash = map_hash(key);
	node->val = ((char *) (node + 1)) + voffset;
	memcpy(node->val, val, vsize);
	return node;
}

static int
map_bucketidx(map_base_t *m, unsigned hash)
{
	return hash & (m->nbuckets - 1);
}

static void
map_addnode(map_base_t *m, map_node_t *node)
{
	int n = map_bucketidx(m, node->hash);
	node->next = m->buckets[n];
	m->buckets[n] = node;
}

static int
map_resize(map_base_t *m, int nbuckets)
{
	map_node_t *nodes = NULL, *node, *next;
	map_node_t **buckets;
	int i = m->nbuckets;
	while (i--) {
		node = (m->buckets)[i];
		while (node) {
			next = node->next;
			node->next = nodes;
			nodes = node;
			node = next;
		}
	}

	buckets = realloc(m->buckets, sizeof(map_node_t) * nbuckets);
	if (buckets) {
		m->buckets = buckets;
		m->nbuckets = nbuckets;
	}

	if (m->buckets) {
		memset(
			m->buckets,
			0,
			sizeof(map_node_t) * m->nbuckets
		);
		node = nodes;
		while (node) {
			next = node->next;
			map_addnode(m, node);
			node = next;
		}
	}
	return (buckets) ? 0 : -1;
}

static map_node_t **
map_getref(map_base_t *m, const char *key)
{
	unsigned hash = map_hash(key);
	map_node_t **next;
	if (m->nbuckets > 0) {
		next = &m->buckets[map_bucketidx(m, hash)];
		while (*next) {
			if ((*next)->hash == hash && !strcmp((char *)(*next + 1), key))
				return next;
		}
		next = &(*next)->next;
	}
	return NULL;
}

void ___map_deinit(map_base_t *m)
{
	map_node_t *next, *node;
	int i = m->nbuckets;
	while (i--) {
		node = m->buckets[i];
		while (node) {
			next = node->next;
			free(node);
			node = next;
		}
	}
	free(m->buckets);
}

void *___map_get(map_base_t *m, const char *key)
{
	map_node_t **next = map_getref(m, key);
	return next ? (*next)->val : NULL;
}

int ___map_set(map_base_t *m, const char *key, void *val, int vsize)
{
	map_node_t **next, *node;
	next = map_getref(m, key);
	if (next) {
		memcpy((*next)->val, val, vsize);
		return 0;
	}

	/* Add node */
	node = map_newnode(key, val, vsize);
	if (!node) goto error;
	if (m->nnodes >= m->nbuckets) {
		int n = (m->nbuckets > 0) ? (m->nbuckets << 1) : 1;
		int err = map_resize(m, n);
		if (err) goto error;
	}
	map_addnode(m, node);
	m->nnodes++;
	return 0;
error:
	if (node) free(node);
	return -1;
}

void ___map_remove(map_base_t *m, const char *key)
{
	map_node_t *node;
	map_node_t **next = map_getref(m, key);
	if (next) {
		node = *next;
		*next = (*next)->next;
		free(node);
		m->nnodes--;
	}
}

map_iter_t ___map_iter()
{
	return (map_iter_t){
		.bucketidx = -1,
		.node = NULL
	};
}

const char *___map_next(map_base_t *m, map_iter_t *iter)
{
	if (iter->node) {
		iter->node = iter->node->next;
		if (iter->node)
			return (char *) (iter->node + 1);
	}
	do {
		if (++iter->bucketidx >= m->nbuckets)
			return NULL;
		iter->node = m->buckets[iter->bucketidx];
	} while (!iter->node);
	return (char *) (iter->node + 1);
}
