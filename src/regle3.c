#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int64_t n;
    int64_t k;
    int64_t j;
    int64_t jmax;
    int64_t i;
    int64_t imax;
    int64_t x1, x2;
    
    if (argc != 2) {
    	fprintf(stderr, "Usage: %s n\n", argv[0]);
    	exit(EXIT_FAILURE);
    }
    
    sscanf(argv[1], "%" PRId64, &n);
    assert(n < 32 && (n & 1) == 0);
    
    jmax = 1 << n;
    
    for (k = 1; k < n; k++) {
        for (j = 0; j < jmax; j++) {
            for (i = 0; i < n; i++) {
                x1 = i*n + 1;
                x2 = i*n + k+1;
                if (!((j >> (n-i-1)) & 1)) {
                    x1 *= -1;
                    x2 *= -1;
                }
                printf("%" PRId64 " %" PRId64 " ", x1, x2);
            }
            printf("%d\n", 0);
        }
    }
    
    imax = 1 << n;
    
    for (k = 1; k < n; k++) {
        for (i = 0; i < imax; i++) {
            for (j = 0; j < n; j++) {
                x1 = 0*n + j+1;
                x2 = k*n + j+1;
                if (!((i >> (n-j-1)) & 1)) {
                    x1 *= -1;
                    x2 *= -1;
                }
                printf("%" PRId64 " %" PRId64 " ", x1, x2);
            }
            printf("%d\n", 0);
        }
    }

    return 0;
}
