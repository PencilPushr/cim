#include "cim_string.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

char* string_init_c(cim_string* string, char from)
{
	assert(string->__data == NULL && "String is already initialzied"
		"Call string_delete on the string to initialize it again");

	string_reserve(string, 2);
	if (string->__data == NULL)
		return NULL;
	string->__data[0] = from;
	string->__data[1] = '\0';
	string->__length = 1;
	return string->__data;
}

char* string_init_ccp(cim_string* string, const char* from)
{
	assert(string->__data == NULL && "String is already initialzied"
		"Call string_delete on the string to initialize it again");

	size_t len = strlen(from);
	size_t size = len + 1;
	string_reserve(string, size);
	if (string->__data == NULL)
		return NULL;
	strcpy_s(string->__data, string->__capacity, from);
	string->__length = len;
	return string->__data;
}

char* string_init_s(cim_string* string, const cim_string* from)
{
	assert(string->__data == NULL &&"String is already initialzied"
		"Call string_delete on the string to initialize it again");

	size_t size = from->__length + 1;
	string_reserve(string, size);
	if (string->__data == NULL)
		return NULL;
	strcpy_s(string->__data, string->__capacity, from->__data);
	string->__length = from->__length;
	return string->__data;
}

void string_delete(cim_string* string)
{
	free(string->__data);
	string->__data = NULL;
}

void string_recalc_size(cim_string* string)
{
	string->__capacity *= 2;
}

char* string_append_ccp(cim_string* to, const char* from)
{
	size_t len = strlen(from);
	size_t size = len + to->__length + 1;
	if (to->__capacity < size)
		string_reserve(to, size);
	strcpy_s(to->__data + to->__length, (to->__capacity) - to->__length, from);
	to->__length += len;
	return to->__data;
}

char* string_append_s(cim_string* to, const cim_string* from)
{
	size_t size = from->__length + to->__length + 1;
	if (to->__capacity < size)
		string_reserve(to, size);
	strcpy_s(to->__data + to->__length, (to->__capacity) - to->__length, from->__data);
	to->__length += from->__length;
	return to->__data;
}

//char* string_append_c(cim_string* to, char from)
//{
//	size_t size = to->__length + 1;
//}

void string_reserve(cim_string* string, size_t size)
{
	char* newBuffer = malloc(size);
	if (newBuffer == NULL)
		return;
	if (string->__length > 0)
		strncpy(newBuffer, string->__data, size);
	if (string->__data != NULL)
		string_delete(string);
	string->__data = newBuffer;
	string->__capacity = size;
}

char* string_at(const cim_string* string, size_t index)
{
	assert(index < string->__length && "String index out of range");
	return string->__data + index;
}

size_t string_length(const cim_string* string)
{
	return string->__length;
}

char* string_front(const cim_string* string)
{
	return string->__data;
}

char* string_back(const cim_string* string)
{
	return string->__data + string->__length;
}

char* string_data(const cim_string* string)
{
	return string->__data;
}

bool string_empty(const cim_string* string)
{
	return string->__length == 0;
}

size_t string_capacity(const cim_string* string)
{
	return string->__capacity - 1;
}

char* string_shrink_to_fit(cim_string* string)
{
	if (string->__capacity - string->__length < 1)
		return NULL;
	string_reserve(string, string->__length + 1);
	return string->__data;
}

void string_clear(cim_string* string)
{
	string->__data[0] = '\0';
	string->__length = 0;
}

bool string_compare_ccp(const cim_string* s1, const cim_string* s2)
{
	return strcmp(string_data(s1), string_data(s2)) == 0;
}

bool string_compare_s(const cim_string* s1, const char* s2)
{
	return strcmp(string_data(s1), s2) == 0;
}


X_TO_CIM_STRING_DEF(short, short);
X_TO_CIM_STRING_DEF(ushort, unsigned short);
X_TO_CIM_STRING_DEF(int, int);
X_TO_CIM_STRING_DEF(uint, unsigned int);
X_TO_CIM_STRING_DEF(long, long);
X_TO_CIM_STRING_DEF(ulong, unsigned long);
X_TO_CIM_STRING_DEF(long_long, long long);
X_TO_CIM_STRING_DEF(ulong_long, unsigned long long);

X_TO_CIM_STRING_DEF(i8, uint8_t);
X_TO_CIM_STRING_DEF(i16, uint16_t);
X_TO_CIM_STRING_DEF(i32, uint32_t);
X_TO_CIM_STRING_DEF(i64, uint64_t);
