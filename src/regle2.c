#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int64_t n;
    int64_t i;
    int64_t j;
    int64_t k;
    
    if (argc != 2) {
    	fprintf(stderr, "Usage: %s n\n", argv[0]);
    	exit(EXIT_FAILURE);
    }
    
    sscanf(argv[1], "%" PRId64, &n);
    assert(n < 32 && (n & 1) == 0);
    
    for (i = 0; i < (n-2); i++) {
    	for (j = 0; j < (n-2); j++) {
    		for (k = 0; k <= 2; k++)
    			printf("%" PRId64 " ", i*n + j+1+k);
    		printf("0\n");
    		
    		for (k = 0; k <= 2; k++)
    			printf("%" PRId64 " ", (i+k)*n + j+1);
    		printf("0\n");
    		
    		for (k = 0; k <= 2; k++)
    			printf("%" PRId64 " ", -i*n - (j+1+k));
    		printf("0\n");
    		
    		for (k = 0; k <= 2; k++)
    			printf("%" PRId64 " ", -(i+k)*n - (j+1));
    		printf("0\n");
    	}
    }

    return 0;
}
