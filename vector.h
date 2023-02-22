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
//https://github.com/eteran/c-vector/blob/master/cvector.h
#endif /* VECTOR_H */
