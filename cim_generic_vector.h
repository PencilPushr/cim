#ifndef _CVECTOR_H_
#define _CVECTOR_H_

#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#include "cim_allocator.h"

#define CIM_GENERIC_VECTOR_TYPE_DEF(name, type)\
\
typedef struct name##_cim_vector \
{\
	type* data; \
	size_t __capacity; \
	size_t __length; \
} name##_cim_vector;

#define CIM_GENERIC_VECTOR_INIT_DECL(name, type)\
type* name##_vector_init_with_capacity(name##_cim_vector* v, size_t cap);

#define CIM_GENERIC_VECTOR_INIT_DEF(name, type) \
type* name##_vector_init_with_capacity(name##_cim_vector* v, size_t cap) \
{\
	assert(cap != 0 && "Vector reservation size cannot be 0");\
	assert(v->data == NULL && "Vector is already initialzied");\
	name##_vector_reserve(v, cap);\
	return v->data;\
}

#define CIM_GENERIC_VECTOR_FREE_DECL(name, type)\
void name##_vector_free(name##_cim_vector* v);

#define CIM_GENERIC_VECTOR_FREE_DEF(name, type) \
void name##_vector_free(name##_cim_vector* v) \
{\
	cim_free(v->data);\
	v->data = NULL;\
	v->__length = 0;\
	v->__capacity = 0;\
}

#define CIM_GENERIC_VECTOR_LENGTH_DECL(name, type)\
size_t name##_vector_length(name##_cim_vector* v);

#define CIM_GENERIC_VECTOR_LENGTH_DEF(name, type) \
size_t name##_vector_length(name##_cim_vector* v) \
{\
	return v->__length;\
}

#define CIM_GENERIC_VECTOR_RESERVE_DECL(name, type)\
type* name##_vector_reserve(name##_cim_vector* v, size_t size);

#define CIM_GENERIC_VECTOR_RESERVE_DEF(name, type) \
type* name##_vector_reserve(name##_cim_vector* v, size_t size) \
{\
	type* newBuffer = cim_malloc(size * sizeof(type));\
	if (newBuffer == NULL)\
		return NULL;\
	if (v->__length > 0)\
		memcpy(newBuffer, v->data, size * sizeof(type));\
	cim_free(v->data);\
	v->data = newBuffer;\
	v->__capacity = size;\
	return v->data;\
}

#define CIM_GENERIC_INIT_VECTOR_FROM_EXISTING_DECL(name, type)\
type* init_##name##_vector_from_existing(name##_cim_vector* v, const name##_cim_vector* from);

#define CIM_GENERIC_INIT_VECTOR_FROM_EXISTING_DEF(name, type) \
type* init_##name##_vector_from_existing(name##_cim_vector* v, const name##_cim_vector* from) \
{\
	assert(v->data == NULL && "Vector is already initialzied");\
	size_t size = from->__length;\
	name##_vector_reserve(v, size);\
	if (v->data == NULL)\
		return NULL;\
	memcpy(v->data, from->data, v->__capacity * sizeof(type));\
	v->__length = from->__length;\
	return v->data;\
}

#define CIM_GENERIC_VECTOR_APPEND_DECL(name, type)\
type* name##_vector_append(name##_cim_vector* v, const type* item);

#define CIM_GENERIC_VECTOR_APPEND_DEF(name, type) \
type* name##_vector_append(name##_cim_vector* v, const type* item) \
{\
	if (v->__capacity < v->__length + 1)\
	{\
		name##_vector_recalc_size(v);\
		name##_vector_reserve(v, v->__capacity); \
	}\
	v->data[v->__length] = *item;\
	v->__length++;\
	return v->data;\
}

#define CIM_GENERIC_VECTOR_RECALC_SIZE_DECL(name, type)\
type* name##_vector_recalc_size(name##_cim_vector* v);

#define CIM_GENERIC_VECTOR_RECALC_SIZE_DEF(name, type)\
type* name##_vector_recalc_size(name##_cim_vector* v)\
{\
	v->__capacity *= 2;\
}

#define CIM_GENERIC_VECTOR_DECL(name, type) \
CIM_GENERIC_VECTOR_TYPE_DEF(name, type)\
CIM_GENERIC_VECTOR_RECALC_SIZE_DECL(name, type)\
CIM_GENERIC_VECTOR_RESERVE_DECL(name, type)\
CIM_GENERIC_VECTOR_INIT_DECL(name, type)\
CIM_GENERIC_VECTOR_FREE_DECL(name, type)\
CIM_GENERIC_VECTOR_LENGTH_DECL(name, type)\
CIM_GENERIC_INIT_VECTOR_FROM_EXISTING_DECL(name, type)\
CIM_GENERIC_VECTOR_APPEND_DECL(name, type)

#define CIM_GENERIC_VECTOR_DEF(name, type) \
CIM_GENERIC_VECTOR_RECALC_SIZE_DEF(name, type)\
CIM_GENERIC_VECTOR_RESERVE_DEF(name, type)\
CIM_GENERIC_VECTOR_INIT_DEF(name, type)\
CIM_GENERIC_VECTOR_FREE_DEF(name, type)\
CIM_GENERIC_VECTOR_LENGTH_DEF(name, type)\
CIM_GENERIC_INIT_VECTOR_FROM_EXISTING_DEF(name, type)\
CIM_GENERIC_VECTOR_APPEND_DEF(name, type)

#endif