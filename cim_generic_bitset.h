#pragma once

#include <inttypes.h>
#include <string.h>
#include <assert.h>

typedef struct cim_byte_bit_index
{
	size_t byte;
	size_t bit;
} cim_byte_bit_index;

#define CIM_GENERIC_BITSET_ZERO_DECL(name, type, size)\
void cim_##name##_bitset_zero(type* bitfield);

#define CIM_GENERIC_BITSET_ZERO_DEF(name, type, size)\
void cim_##name##_bitset_zero(type* bitfield)\
{\
	memset(bitfield, 0, sizeof(type) * size);\
}

#define CIM_GENERIC_BITSET_GET_BIT_BYTE_INDEX_DECL(type, size)\
cim_byte_bit_index cim_get_byte_bit_index(size_t field_size, size_t index);

#define CIM_GENERIC_BITSET_GET_BIT_BYTE_INDEX_DEF(type, size)\
cim_byte_bit_index cim_get_byte_bit_index(size_t field_size, size_t index)\
{\
	size_t word_size = sizeof(type) * 8;\
	size_t which_byte = (size_t)(index / (float)word_size);\
	size_t which_bit = (size_t)(index - (which_byte * word_size));\
	cim_byte_bit_index byte_bit_index;\
	byte_bit_index.byte = which_byte;\
	byte_bit_index.bit = which_bit;\
	return byte_bit_index;\
}

#define CIM_GENERIC_BITSET_SET_BIT_DECL(name, type, size)\
void cim_##name##_bitset_set(type* bitfield, size_t index);

#define CIM_GENERIC_BITSET_SET_BIT_DEF(name, type, size)\
void cim_##name##_bitset_set(type* bitfield, size_t index)\
{\
	assert(index < size && "Bitset index out of range");\
	cim_byte_bit_index byte_bit_index = cim_get_byte_bit_index(size, index);\
	bitfield[byte_bit_index.byte] |= 1 << byte_bit_index.bit;\
}


#define CIM_GENERIC_BITSET_CLEAR_BIT_DECL(name, type, size)\
void cim_##name##_bitset_clear(type* bitfield, size_t index);

#define CIM_GENERIC_BITSET_CLEAR_BIT_DEF(name, type, size)\
void cim_##name##_bitset_clear(type* bitfield, size_t index)\
{\
	assert(index < size && "Bitset index out of range");\
	cim_byte_bit_index byte_bit_index = cim_get_byte_bit_index(size, index);\
	bitfield[byte_bit_index.byte] &= ~(1 << byte_bit_index.bit);\
}


#define CIM_GENERIC_BITSET_CHECK_BIT_DECL(name, type, size)\
bool cim_##name##_bitset_check(type* bitfield, size_t index);

#define CIM_GENERIC_BITSET_CHECK_BIT_DEF(name, type, size)\
bool cim_##name##_bitset_check(type* bitfield, size_t index)\
{\
	assert(index < size && "Bitset index out of range");\
	cim_byte_bit_index byte_bit_index = cim_get_byte_bit_index(size, index);\
	return bitfield[byte_bit_index.byte] & (1 << byte_bit_index.bit);\
}

#define CIM_GENERIC_BITSET_DECL(name, type, size)\
CIM_GENERIC_BITSET_GET_BIT_BYTE_INDEX_DECL(type, size)\
CIM_GENERIC_BITSET_SET_BIT_DECL(name, type, size)\
CIM_GENERIC_BITSET_CHECK_BIT_DECL(name, type, size)\
CIM_GENERIC_BITSET_ZERO_DECL(name, type, size)\
CIM_GENERIC_BITSET_CLEAR_BIT_DECL(name, type, size)

#define CIM_GENERIC_BITSET_DEF(name, type, size)\
CIM_GENERIC_BITSET_GET_BIT_BYTE_INDEX_DEF(type, size)\
CIM_GENERIC_BITSET_SET_BIT_DEF(name, type, size)\
CIM_GENERIC_BITSET_CHECK_BIT_DEF(name, type, size)\
CIM_GENERIC_BITSET_ZERO_DEF(name, type, size)\
CIM_GENERIC_BITSET_CLEAR_BIT_DEF(name, type, size)