#ifndef _DUMB_SHM_STRUCT
#define _DUMB_SHM_STRUCT

#include <stdint.h>
#include <stdlib.h>

struct cyclic_buf
{
	volatile uint64_t pos;
	volatile int array[128][4096];
};

#endif
