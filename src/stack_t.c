#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <stack_t.h>

void
stack_init(stack_t *stack)
{
	stack->max = N_MAX_STACK;
	stack->pos = 0;
	stack->array = malloc(sizeof(int64_t) * stack->max);
}

int
stack_is_empty(stack_t *stack)
{
	return stack->pos == 0;
}

int64_t
stack_top(stack_t *stack)
{
	return stack->array[stack->pos-1];
}

int64_t
stack_size(stack_t *stack)
{
	return stack->pos;
}

void
stack_print(stack_t *stack) {
	int64_t i;
	
	for (i = 0; i < stack->pos; i++)
		printf("%" PRId64 " ", stack->array[i]);
}

void
stack_free(stack_t *stack)
{
	free(stack->array);
}

void
stack_empty(stack_t *stack)
{
	stack_free(stack);
	stack_init(stack);
}

void
stack_push(stack_t *stack, int64_t x)
{
	if (stack->pos >= stack->max) {
		stack->max *= 2;
		stack->array = realloc(stack->array, sizeof(int64_t) * stack->max);
	}
	stack->array[stack->pos] = x;
	stack->pos++;
}

int64_t
stack_pop(stack_t *stack)
{
	stack->pos--;
	return stack->array[stack->pos];
}

int64_t
stack_duplicate(stack_t *stack, int64_t index)
{
	stack_push(stack, stack->array[index]);
	return stack_size(stack) - 1;
}
