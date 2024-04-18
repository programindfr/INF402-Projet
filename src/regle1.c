#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack_t.h"

void
set_bit(int64_t *x, int64_t kthBit)
{
	*x |= (1 << kthBit);
}

void
clear_bit(int64_t *x, int64_t kthBit)
{
	*x &= ~(1 << kthBit);
}

void
ensemble_fill(stack_t *stack, int64_t index, int64_t kthBit, int64_t temperature, int64_t n)
{
	if (kthBit < (n-1)) {
		clear_bit(&stack->array[index], kthBit);
		ensemble_fill(stack, index, kthBit+1, temperature-1, n);
		int64_t indexBis = stack_duplicate(stack, index);
		set_bit(&stack->array[indexBis], kthBit);
		ensemble_fill(stack, indexBis, kthBit+1, temperature+1, n);
	} else {
		switch (temperature) {
		case -1:
			clear_bit(&stack->array[index], kthBit);
			break;
		
		case 1:
			set_bit(&stack->array[index], kthBit);
			break;
		
		default:
			clear_bit(&stack->array[index], kthBit);
			int64_t indexBis = stack_duplicate(stack, index);
			set_bit(&stack->array[indexBis], kthBit);
			break;
		}
	}
}

int
main(int argc, char *argv[])
{
    int64_t n;
    int64_t e;
    int64_t i;
    int64_t j;
    int64_t k;
    int64_t x;
    stack_t stack;
    
    if (argc != 2) {
    	fprintf(stderr, "Usage: %s n\n", argv[0]);
    	exit(EXIT_FAILURE);
    }
    
    sscanf(argv[1], "%" PRId64, &n);
    assert(n < 32 && (n & 1) == 0);
    
    stack_init(&stack);
    stack_push(&stack, 0);
    ensemble_fill(&stack, 0, 0, 0, n);
    
    for (e = 0; e < stack.pos; e++) {
    	for (i = 0; i < n; i++) {
    		for (k = 0; k < n; k++) {
    			x = i*n + (k+1);
                if (!((stack.array[e] >> k) & 1))
                    x *= -1;
                printf("%" PRId64 " ", x);
    		}
    		printf("0\n");
    	}
    	
    	for (j = 0; j < n; j++) {
    		for (k = 0; k < n; k++) {
    			x = k*n + (j+1);
                if (!((stack.array[e] >> k) & 1))
                    x *= -1;
                printf("%" PRId64 " ", x);
    		}
    		printf("0\n");
    	}
    }

    return 0;
}
