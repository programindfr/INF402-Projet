#ifndef __STACK_T_H__
#define __STACK_T_H__

#include <stdint.h>

#define N_MAX_STACK 1

struct stack {
	int64_t max;
	int64_t pos;
	int64_t *array;
};
typedef struct stack stack_t;

void stack_init(stack_t *stack);
int stack_is_empty(stack_t *stack);
int64_t stack_top(stack_t *stack);
int64_t stack_size(stack_t *stack);
void stack_print(stack_t *stack);

void stack_empty(stack_t *stack);
void stack_push(stack_t *stack, int64_t x);
int64_t stack_pop(stack_t *stack);
int64_t stack_duplicate(stack_t *stack, int64_t index);

#endif//__STACK_T_H__
