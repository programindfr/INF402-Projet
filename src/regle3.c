#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include <regle3.h>

void
regle3_n(int64_t n, FILE *output)
{
    int64_t i1, j1, i, j, k, x1, x2;
    int64_t imax = 1 << n;
    int64_t jmax = 1 << n;
    
    assert(n > 0 && n < 32 && (n & 1) == 0);
    
    for (j1 = 0; j1 < (n-1); j1++) {
		for (k = (j1+1); k < n; k++) {
		    for (j = 0; j < jmax; j++) {
		        for (i = 0; i < n; i++) {
		            x1 = i*n + j1+1;
		            x2 = i*n + k+1;
		            if (!((j >> (n-i-1)) & 1)) {
		                x1 *= -1;
		                x2 *= -1;
		            }
		            fprintf(output, "%" PRId64 " %" PRId64 " ", x1, x2);
		        }
		        fprintf(output, "0\n");
		    }
		}
	}
    
    for (i1 = 0; i1 < (n-1); i1++) {
    	for (k = (i1+1); k < n; k++) {
		    for (i = 0; i < imax; i++) {
		        for (j = 0; j < n; j++) {
		            x1 = i1*n + j+1;
		            x2 = k*n + j+1;
		            if (!((i >> (n-j-1)) & 1)) {
		                x1 *= -1;
		                x2 *= -1;
		            }
		            fprintf(output, "%" PRId64 " %" PRId64 " ", x1, x2);
		        }
		        fprintf(output, "0\n");
		    }
		}
    }
}
