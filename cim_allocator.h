#pragma once
#include <stdbool.h>

#if defined(DEBUG) || defined(_DEBUG)
	#ifdef CIM_TRACK_MEMORY_ALLOCATIONS
		#undef CIM_TRACK_MEMORY_ALLOCATIONS
	#endif
	#define CIM_TRACK_MEMORY_ALLOCATIONS
#endif

void* cim_malloc(size_t size);
void cim_free(void* ptr);
size_t cim_allocated_size_of(void* ptr);

size_t cim_total_allocated_memory();
size_t cim_total_deallocated_memory();
size_t cim_total_allocation_calls();
size_t cim_total_deallocated_calls();
void cim_break_if_leak();


#ifdef CIM_TRACK_MEMORY_ALLOCATIONS
	union cim_aligned_size
	{
		size_t size;
		//currently long double is used as alignment requirement
		//since i cant find max_align_t because C in msvc is retarded.
		long double align;
	};
#endif
