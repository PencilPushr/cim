#include "cim_string.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


char* string_init_c(cim_string* string, char from)
{
	assert(string->data == NULL && "String is already initialzied"
		"Call string_delete on the string to initialize it again");

	string_reserve(string, 2);
	if (string->data == NULL)
		return NULL;
	string->data[0] = from;
	string->data[1] = '\0';
	string->__length = 1;
	return string->data;
}

char* string_init_ccp(cim_string* string, const char* from)
{
	assert(string->data == NULL && "String is already initialzied"
		"Call string_delete on the string to initialize it again");

	size_t len = strlen(from);
	size_t size = len + 1;
	string_reserve(string, size);
	if (string->data == NULL)
		return NULL;
	strcpy_s(string->data, string->__capacity, from);
	string->__length = len;
	return string->data;
}

char* string_init_s(cim_string* string, const cim_string* from)
{
	assert(string->data == NULL &&"String is already initialzied"
		"Call string_delete on the string to initialize it again");

	size_t size = from->__length + 1;
	string_reserve(string, size);
	if (string->data == NULL)
		return NULL;
	strcpy_s(string->data, string->__capacity, from->data);
	string->__length = from->__length;
	return string->data;
}

void string_free(cim_string* string)
{
	cim_free(string->data);
	string->data = NULL;
	string->__length = 0;
	string->__capacity = 0;
}

//void string_recalc_size(cim_string* string)
//{
//	string->__capacity *= 2;
//}

char* string_append_ccp(cim_string* to, const char* from)
{
	size_t len = strlen(from);
	size_t size = len + to->__length + 1;
	if (to->__capacity < size)
		string_reserve(to, size);
	strcpy_s(to->data + to->__length, (to->__capacity) - to->__length, from);
	to->__length += len;
	return to->data;
}

char* string_append_s(cim_string* to, const cim_string* from)
{
	size_t size = from->__length + to->__length + 1;
	if (to->__capacity < size)
		string_reserve(to, size);
	strcpy_s(to->data + to->__length, (to->__capacity) - to->__length, from->data);
	to->__length += from->__length;
	return to->data;
}

char* string_append_c(cim_string* to, char from)
{
	size_t size = to->__length + 2;
	if (to->__capacity < size)
		string_reserve(to, size);
	*(to->data + to->__length) = from;
	*(to->data + to->__length + 1) = '\0';
	to->__length++;
	return to->data;
}

char* string_reserve(cim_string* string, size_t size)
{
	//assert(size != 0 && "String reservation size cannot be 0"); maybe do this
	char* newBuffer = cim_malloc(size);
	if (newBuffer == NULL)
		return NULL;
	if (string->__length > 0)
		strncpy(newBuffer, string->data, size);
	cim_free(string->data);
	string->data = newBuffer;
	string->__capacity = size;
	return string->data;
}

char* string_at(const cim_string* string, size_t index)
{
	assert(index < string->__length && "String index out of range");
	return string->data + index;
}

size_t string_length(const cim_string* string)
{
	return string->__length;
}

char* string_front(const cim_string* string)
{
	return string->data;
}

char* string_back(const cim_string* string)
{
	return string->data + string->__length - 1;
}

char* string_data(const cim_string* string)
{
	return string->data;
}

bool string_empty(const cim_string* string)
{
	return string->__length == 0;
}

size_t string_capacity(const cim_string* string)
{
	return string->__capacity;
}

char* string_shrink_to_fit(cim_string* string)
{
	if (string->__capacity - string->__length < 1)
		return NULL;
	string_reserve(string, string->__length + 1);
	return string->data;
}

void string_clear(cim_string* string)
{
	string->data[0] = '\0';
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
