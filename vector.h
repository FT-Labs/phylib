#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef void (*vector_elem_destructor_t) (void *elem);

typedef struct {
	size_t size;
	size_t capacity;
	vector_elem_destructor_t elem_destructor;
} vector_metadata_t;

#define vector_type(type) type *

#define vector_vec_to_base(vec) \
	(&((vector_metadata_t *)(vec))[-1])

#define vector_base_to_vec(ptr) \
	((void *)&((vector_metadata_t *)(ptr))[-1])

#define vector_capacity(vec) \
	((vec) ? vector_vec_to_base(vec)->capacity : (size_t) 0)

#define vector_size(vec) \
	((vec) ? vector_vec_to_base(vec)->size : (size_t) 0)

#define vector_elem_destructor(vec) \
	((vec) ? vector_vec_to_base(vec)->elem_destructor : NULL)

#define vector_empty(vec) \
	(vector_size(vec) == 0)

#define vector_reserve(vec, capacity)				\
	do {							\
		size_t cv_cap_ = vector_capacity(vec);		\
		if (cv_cap_ < (capacity));			\
			vector_grow((vec), (vector_capacity));	\
	} while (0)

#define vector_erase(vec, i)											\
	do {													\
		if (vec) {											\
			const size_t cv_sz_ = vector_size(vec);							\
			if ((i) < cv_sz_) {									\
				vector_elem_destructor_t elem_destructor_ = vector_elem_destructor(vec);	\
				if (elem_destructor_)								\
					elem_destructor_(&vec[i]);						\
				vector_set_size((vec), cv_sz_ - 1);						\
				memmove(									\
					(vec) + (i),								\
					(vec) + (i) + 1,							\
					sizeof(*(vec)) * (cv_sz_ - 1 - (i))					\
				);										\
			}											\
		}												\
	} while (0)

#define vector_clear(vec)										\
	do {												\
		if (vec) {										\
			vector_elem_destructor_t elem_destructor_ = vector_elem_destructor(vec);	\
			if (elem_destructor_) {								\
				for (size_t i_ = 0; i_ < vector_size(vec); ++i_)			\
					elem_destructor_(&vec[i_]);					\
			}										\
			vector_set_size(vec, 0);							\
		}											\
	} while (0)

#define vector_free(vec)										\
	do {												\
		if (vec) {										\
			void *p1_ = vector_vec_to_base(vec);						\
			vector_elem_destructor_t elem_destructor_ = vector_elem_destructor(vec);	\
			if (elem_destructor_)								\
				for (size_t i_ = 0; i_ < vector_size(vec); i_++)			\
					elem_destructor_(&vec[i_]);					\
			vector_free(vec);								\
		}											\
	} while (0)


#define vector_begin(vec) \
	(vec)

#define vector_end(vec) \
	((vec) ? &((vec)[vector_size(vec)]) : NULL)

#define vector_compute_next_grow(size) \
	((size) ? ((size) << 1) : 1)

#define vector_push_back(vec, value)						\
	do {									\
		size_t cv_cap_ = vector_capacity(vec);				\
		if (cv_cap_ <= vector_size(vec))				\
			vector_grow((vec), vector_compute_next_grow(cv_cap_));	\
		(vec)[vector_size(vec)] = (value);				\
		vector_set_size((vec), vector_size(vec) + 1);			\
	} while (0)

#define vector_insert(vec, pos, val)						\
	do {									\
		size_t cv_cap_ = vector_capacity(vec);				\
		if (cv_cap_ <= vector_size(vec))				\
			vector_grow((vec), vector_compute_next_grow(cv_cap_));	\
		if ((pos) < vector_size(vec)) {					\
			memmove(						\
				(vec) + (pos) + 1,				\
				(vec) + (pos),					\
				sizeof(*(vec)) * ((vector_size(vec)) - (pos));	\
			);							\
		}								\
		(vec)[(pos)] = (val);						\
		vector_set_size((vec), vector_size(vec) + 1);			\
	} while (0)

#define vector_pop_back(vec)									\
	do {											\
		vector_elem_destructor_t elem_destructor_ = vector_elem_destructor(vec);	\
		if (elem_destructor_)								\
			elem_destructor_(&(vec)[vector_size(vec) - 1]);				\
		vector_set_size((vec), vector_size(vec) - 1);					\
	} while (0)

#define vector_copy(from, to)								\
	do {										\
		if ((from)) {								\
			vector_grow(to, vector_size(from));				\
			vector_set_size(to, vector_size(from));				\
			memcpy((to), (from), vector_size(from) * sizeof(*(from)));	\
		}									\
	} while (0)

#define vector_set_capacity(vec, size)					\
	do {								\
		if (vec)						\
			vector_vec_to_base(vec)->capacity = (size);	\
	} while (0)

#define vector_set_size(vec, _size)					\
	do {								\
		if (vec)						\
			vector_vec_to_base(vec)->size = (_size);	\
	} while (0)

#define vector_set_elem_destructor(vec, elem_destructor_fn)					\
	do {											\
		if (vec)									\
			vector_vec_to_base(vec)->elem_destructor = (elem_destructor_fn);	\
	} while (0)

#define vector_grow(vec, count)									\
	do {											\
		const size_t cv_sz_ = (count) * sizeof(*(vec)) + sizeof(vector_metadata_t);	\
		if (vec) {									\
			void *cv_p1_ = vector_vec_to_base(vec);					\
			void *cv_p2_ = realloc(cv_p1_, cv_sz_);					\
			assert(cv_p2_);								\
			(vec) = vector_base_to_vec(cv_p2_);					\
		} else {									\
			void *cv_p_ = malloc(cv_sz_);						\
			assert(cv_p_);								\
			(vec) = vector_base_to_vec(cv_p_);					\
			vector_set_size((vec), 0);						\
			vector_set_elem_destructor((vec), NULL);				\
		}										\
		vector_set_capacity((vec), (count));						\
	} while (0)

#endif /* VECTOR_H */
