#pragma once
#include <stddef.h>

#include <stdio.h>
#include <assert.h>


#define CIM_GENERIC_STATIC_QUEUE_TYPE_DEF(name, type, size)\
typedef struct static_##name##_queue \
{\
	type __data[size];\
	size_t __head;\
	size_t __tail;\
	size_t count;\
} static_##name##_queue;

#define CIM_GENERIC_STATIC_QUEUE_INIT_DECL(name, type)\
void cim_init_static_##name##_queue(static_##name##_queue* queue);

#define CIM_GENERIC_STATIC_QUEUE_PUSH_DECL(name, type)\
void cim_static_##name##_queue_push(static_##name##_queue* queue, type* data);

#define CIM_GENERIC_STATIC_QUEUE_POP_DECL(name, type)\
type* cim_static_##name##_queue_pop(static_##name##_queue** queue);

#define CIM_GENERIC_STATIC_QUEUE_PEEKBACK_DECL(name, type)\
type* cim_static_##name##_queue_peekback(static_##name##_queue* queue);

#define CIM_GENERIC_STATIC_QUEUE_PEEKFRONT_DECL(name, type)\
type* cim_static_##name##_queue_peekfront(static_##name##_queue* queue);

#define CIM_GENERIC_STATIC_QUEUE_EMPTY_DECL(name, type)\
bool cim_static_##name##_queue_empty(static_##name##_queue* queue);

#define CIM_GENERIC_STATIC_QUEUE_DECL(name, type, size)\
CIM_GENERIC_STATIC_QUEUE_TYPE_DEF(name, type, size)\
CIM_GENERIC_STATIC_QUEUE_INIT_DECL(name, type)\
CIM_GENERIC_STATIC_QUEUE_PUSH_DECL(name, type)\
CIM_GENERIC_STATIC_QUEUE_POP_DECL(name, type)\
CIM_GENERIC_STATIC_QUEUE_PEEKBACK_DECL(name, type)\
CIM_GENERIC_STATIC_QUEUE_PEEKFRONT_DECL(name, type)

#define CIM_GENERIC_STATIC_QUEUE_INIT_DEF(name)\
void cim_init_static_##name##_queue(static_##name##_queue* queue)\
{\
	queue->__head = 0;\
	queue->__tail = 0;\
	queue->count = 0;\
}

#define CIM_GENERIC_STATIC_QUEUE_PUSH_DEF(name, type, size)\
void cim_static_##name##_queue_push(static_##name##_queue* queue, type* thing)\
{\
	assert(queue->count < size && "Cannot push to a full queue");\
	queue->count++;\
	queue->__data[queue->__tail] = *thing;\
	queue->__tail = ++queue->__tail % size;\
}

#define CIM_GENERIC_STATIC_QUEUE_POP_DEF(name, type, size)\
type* cim_static_##name##_queue_pop(static_##name##_queue* queue)\
{\
	assert(queue->count != 0 && "Cannot pop from an empty queue");\
	queue->count--;\
	type* out = queue->__data + queue->__head;\
	queue->__head = ++queue->__head % size;\
	return out;\
}

#define CIM_GENERIC_STATIC_QUEUE_PEEKFRONT_DEF(name, type)\
type* cim_static_##name##_queue_peekback(static_##name##_queue* queue)\
{\
	return queue->__data + queue->__tail;\
}

#define CIM_GENERIC_STATIC_QUEUE_PEEKBACK_DEF(name, type)\
type* cim_static_##name##_queue_peekfront(static_##name##_queue* queue)\
{\
	return queue->__data + queue->__head;\
}

#define CIM_GENERIC_STATIC_QUEUE_DEF(name, type, size)\
CIM_GENERIC_STATIC_QUEUE_INIT_DEF(name)\
CIM_GENERIC_STATIC_QUEUE_PUSH_DEF(name, type, size)\
CIM_GENERIC_STATIC_QUEUE_POP_DEF(name, type, size)\
CIM_GENERIC_STATIC_QUEUE_PEEKBACK_DEF(name, type)\
CIM_GENERIC_STATIC_QUEUE_PEEKFRONT_DEF(name, type)