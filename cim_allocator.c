#include "cim_allocator.h"

#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

#ifdef CIM_TRACK_MEMORY_ALLOCATIONS
	static size_t _total_allocated_memory = 0;
	static size_t _total_deallocated_memory = 0;
	static size_t total_allocation_calls = 0;
	static size_t total_free_calls = 0;
#endif

void* cim_malloc(size_t size)
{
#ifdef CIM_TRACK_MEMORY_ALLOCATIONS
	total_allocation_calls++;
	union cim_aligned_size* ptr = malloc(sizeof(union cim_aligned_size) + size);
	if (ptr != NULL)
	{
		ptr->size = size;
		_total_allocated_memory += size;
		ptr++;
	}
	return ptr;
#else
	return malloc(size);
#endif
}

void cim_free(void* ptr)
{
#ifdef CIM_TRACK_MEMORY_ALLOCATIONS
	if (ptr != NULL) 
	{
		total_free_calls++;
		union cim_aligned_size* _ptr = ptr;
		_ptr--;
		_total_deallocated_memory += (sizeof * _ptr + _ptr->size) - sizeof(size_t);
		free(_ptr);
	}
#else
	free(ptr);
#endif
}

size_t cim_allocated_size_of(void* ptr)
{
#ifdef CIM_TRACK_MEMORY_ALLOCATIONS
	if (ptr != NULL) 
	{
		union cim_aligned_size* _ptr = ptr;
		_ptr--;
		return _ptr->size;
	}
	return 0;
#endif
	return 0;
}

size_t cim_total_allocated_memory()
{
#ifdef CIM_TRACK_MEMORY_ALLOCATIONS
	return _total_allocated_memory;
#else
	return 0;
#endif
}

size_t cim_total_deallocated_memory()
{
#ifdef CIM_TRACK_MEMORY_ALLOCATIONS
	return _total_deallocated_memory;
#else
	return 0;
#endif
}

void cim_break_if_leak()
{
	assert(cim_total_allocated_memory() == cim_total_deallocated_memory() &&
	"Memory leak detected");
}
