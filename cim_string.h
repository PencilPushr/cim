#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "cim_allocator.h"

typedef struct cim_string
{
	char* data;
	size_t __length;
	size_t __capacity;
} cim_string;

char* string_reserve(cim_string* string, size_t size);

//void string_recalc_size(cim_string* string);

char* string_init_c(cim_string* string, char from);
char* string_init_ccp(cim_string* string, const char* from);
char* string_init_s(cim_string* string, const cim_string* from);

void string_free(cim_string* string);

char* string_append_c(cim_string* to, char from);
char* string_append_ccp(cim_string* to, const char* from);
char* string_append_s(cim_string* to, const cim_string* from);

char* string_at(const cim_string* string, size_t index);
size_t string_length(const cim_string* string);
char* string_front(const cim_string* string);
char* string_back(const cim_string* string);
bool string_empty(const cim_string* string);
char* string_data(const cim_string* string);
size_t string_capacity(const cim_string* string);

char* string_shrink_to_fit(cim_string* string);
void string_clear(cim_string* string);

bool string_compare_ccp(const cim_string* s1, const cim_string* s2);
bool string_compare_s(const cim_string* s1, const char* s2);

// Algorithm for conversion is "char* version 0.4" from http://www.strudel.org.uk/itoa/
#define X_TO_CIM_STRING_DEF(name, type)																						\
																															\
cim_string name##_to_cim_string(type value)																					\
{																															\
	cim_string string = { 0 };																								\
																															\
	if (value == 0)																											\
	{																														\
		string_init_c(&string, '0');																						\
		return string;																										\
	}																														\
																															\
	string_reserve(&string, (size_t)log10(abs(value)) + 1 + (value > 0 ? 0 : 1)); 											\
	if (string.data == NULL)																								\
		return string;																										\
																															\
	type base = 10;																											\
																															\
	if (base < 2 || base > 36)																								\
		return string;																										\
																															\
	char* ptr = string.data, *ptr1 = string.data, tmp_char;																	\
	type tmp_value;																											\
																															\
	do {																													\
		tmp_value = value;																									\
		value /= base;																										\
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];\
		string.__length++;																									\
	} while (value);																										\
																															\
	if (tmp_value < 0)																										\
	{																														\
		string.__length++;																									\
		*ptr++ = '-';																										\
	}																														\
	*ptr-- = '\0';																											\
	while (ptr1 < ptr) {																									\
		tmp_char = *ptr;																									\
		*ptr-- = *ptr1;																										\
		*ptr1++ = tmp_char;																									\
	}																														\
																															\
	return string;																											\
}

#define X_TO_CIM_STRING_DECL(name, type) cim_string name##_to_cim_string(type value) 

X_TO_CIM_STRING_DECL(short, short);
X_TO_CIM_STRING_DECL(ushort, unsigned short);
X_TO_CIM_STRING_DECL(int, int);
X_TO_CIM_STRING_DECL(uint, unsigned int);
X_TO_CIM_STRING_DECL(long, long);
X_TO_CIM_STRING_DECL(ulong, unsigned long);
X_TO_CIM_STRING_DECL(long_long, long long);
X_TO_CIM_STRING_DECL(ulong_long, unsigned long long);

X_TO_CIM_STRING_DECL(i8, uint8_t);
X_TO_CIM_STRING_DECL(i16, uint16_t);
X_TO_CIM_STRING_DECL(i32, uint32_t);
X_TO_CIM_STRING_DECL(i64, uint64_t);
