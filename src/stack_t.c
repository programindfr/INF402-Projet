#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <stack_t.h>

/*
La fonction stack_init prend en parametre un pointeur vers une structure stack_t.
Elle initialise la pile.

parametres
	stack: pointeur vers une structure stack_t

retour
	la pile initialisée
*/
void
stack_init(stack_t *stack)
{
	stack->max = N_MAX_STACK;
	stack->pos = 0;
	stack->array = malloc(sizeof(int64_t) * stack->max);
}

/*
La fonction stack_is_empty vérifie si la pile est vide.
paramètres
	stack: pointeur vers une structure stack_t

retour
	1 si la pile est vide, 0 sinon
*/
int
stack_is_empty(stack_t *stack)
{
	return stack->pos == 0;
}

/*
La fonction stack_top retourne la valeur du sommet de la pile sans la retirer.
paramètres
	stack: pointeur vers une structure stack_t

retour
	la valeur du sommet de la pile
*/
int64_t
stack_top(stack_t *stack)
{
	return stack->array[stack->pos-1];
}

/*
La fonction stack_size retourne la taille de la pile.
paramètres
	stack: pointeur vers une structure stack_t

retour
	la taille de la pile
*/
int64_t
stack_size(stack_t *stack)
{
	return stack->pos;
}

/*
La fonction stack_print affiche les éléments de la pile.

paramètres
	stack: pointeur vers une structure stack_t

retour
	les éléments de la pile
*/
void
stack_print(stack_t *stack) {
	int64_t i;
	
	for (i = 0; i < stack->pos; i++)
		printf("%" PRId64 " ", stack->array[i]);
}


/*
La fonction stack_free libère la mémoire occupée par le tableau de la pile.
paramètres
	stack: pointeur vers une structure stack_t
*/
void
stack_free(stack_t *stack)
{
	free(stack->array);
}

/*
La fonction stack_empty vide la pile en libérant la mémoire occupée par le tableau de la pile.
Ensuite, elle réinitialise la pile en appelant la fonction stack_init.
paramètres
	stack: pointeur vers une structure stack_t
*/
void
stack_empty(stack_t *stack)
{
	stack_free(stack);
	stack_init(stack);
}

/*
La fonction stack_push ajoute un élément à la pile.
paramètres
	stack: pointeur vers une structure stack_t
	x: valeur à ajouter à la pile
*/
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

/*
La fonction stack_pop retire et retourne l'élément en haut de la pile.
paramètres
	stack: pointeur vers une structure stack_t

retour
	l'élément en haut de la pile
*/
int64_t
stack_pop(stack_t *stack)
{
	stack->pos--;
	return stack->array[stack->pos];
}

/*
La fonction stack_duplicate duplique un élément de la pile à un index donné.
paramètres
	stack: pointeur vers une structure stack_t
	index: index de l'élément à dupliquer

retour
	l'index de la copie de l'élément dans la pile
*/
int64_t
stack_duplicate(stack_t *stack, int64_t index)
{
	stack_push(stack, stack->array[index]);
	return stack_size(stack) - 1;
}
