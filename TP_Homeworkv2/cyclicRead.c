#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "cyclicBuf.h"
#include "gen.h"
#include "gen.c"

int main() {
	int memFd = shm_open( "simple_memory", O_RDONLY, 0 );
	if( memFd == -1 ) {
		perror("Can't open file");
		return 1;
	}

	struct cyclic_buf* mem = mmap( NULL, sizeof(struct cyclic_buf), PROT_READ, MAP_SHARED, memFd, 0 );
	if( mem == NULL ) {
		perror("Can't mmap");
		return -1;
	}	

	uint64_t pos = mem->pos;
	printf("starting at %ld\n", pos);
	
	uint64_t seed, old_seed;
	bool first = true;
	while(true) {
		while(mem->pos == pos);

		if(mem->pos >= pos + 128) {
			printf("Failed at %ld\n", pos % 128);
			return 1;
		}

		int seed = verify((void*)mem->array[pos % 128]);
		if(seed == -1) {
			printf("Failed at %ld\n", pos % 128);
			return 1;
		}
		else {
			printf("passed %ld\n", pos % 128);
		}

		if(first){
        	old_seed = seed;
            first = false;
	    }
	    else if(old_seed + 1 != seed) {
	        printf("Failed at %ld\n", pos % 128);
			return 1;
		}
		else {
			old_seed = seed;
		}
		pos++;
	}

	return 0;
}
