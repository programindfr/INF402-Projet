#ifndef __REGLE1_H__
#define __REGLE1_H__

#include <stdint.h>

#include <stack_t.h>

void set_bit(int64_t *x, int64_t kthBit);
void clear_bit(int64_t *x, int64_t kthBit);
void ensemble_create(stack_t *stack, int64_t n);
void ensemble_fill(stack_t *stack, int64_t index, int64_t kthBit, int64_t temperature, int64_t n);
void regle1_n(int64_t n, stack_t *stack, FILE *output);

#endif//__REGLE1_H__
