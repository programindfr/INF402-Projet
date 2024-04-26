#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include <regle1.h>
#include <stack_t.h>

/*
Met le kème bit de l'entier donné à 1.
 
parametre:
  	x Le pointeur vers l'entier.
  	kthBit La position du bit à mettre à 1 (indexé à partir de 0).
*/
void
set_bit(int64_t *x, int64_t kthBit)
{
	*x |= (1 << kthBit);
}

/*
La fonction clear_bit prend en parametre un x et un entier kthBit.
Elle met le bit le plus a droite de x a 0 en effectuant une opération AND entre x et le complément à 1 de 1 décalé de kthBit bits vers la gauche.
parametres
	x: pointeur vers un entier de 64 bits
	kthBit: entier de 64 bits
*/
void
clear_bit(int64_t *x, int64_t kthBit)
{
	*x &= ~(1 << kthBit);
}

/*
La fonction ensemble_create prend en parametre un pointeur vers une structure stack_t et un entier n.
Elle initialise la pile et ajoute un élément à la pile.

parametres
	stack: pointeur vers une structure stack_t
	n: entier de 64 bits

retour
	la pile initialisée    
*/
void
ensemble_create(stack_t *stack, int64_t n)
{
	stack_init(stack);
    stack_push(stack, 0);
    ensemble_fill(stack, 0, 0, 0, n);
}


/*
La fonction ensemble_fill prend en parametre un pointeur vers une structure stack_t, un entier index, un entier kthBit, un entier temperature et un entier n.
Elle remplit la pile avec les éléments de l'ensemble.

parametres
	stack: pointeur vers une structure stack_t
	index: entier de 64 bits
	kthBit: entier de 64 bits
	temperature: entier de 64 bits
	n: entier de 64 bits

retour
	la pile remplie
*/
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


/*
La fonction regle1_n prend en paramètre un entier n, un pointeur vers une structure stack_t et un pointeur vers un fichier output.
Elle génère les clauses correspondantes à la règle 1 pour un ensemble de taille n et les écrit dans le fichier output.
paramètres
	n: entier de 64 bits
	stack: pointeur vers une structure stack_t
	output: pointeur vers un fichier
*/
void
regle1_n(int64_t n, stack_t *stack, FILE *output)
{
    int64_t e, i, j, k, x;
    
    assert(n > 0 && n < 32 && (n & 1) == 0);
    
    for (e = 0; e < stack->pos; e++) {			//En sachant que e est un element des combinaisons pas possibles
    	for (i = 0; i < n; i++) {
    		for (k = 0; k < n; k++) {
    			x = i*n + (k+1);
                if (!((stack->array[e] >> k) & 1))
                    x *= -1;
                fprintf(output, "%" PRId64 " ", x);
    		}
    		fprintf(output, "0\n");
    	}
    	
    	for (j = 0; j < n; j++) {
    		for (k = 0; k < n; k++) {
    			x = k*n + (j+1);
                if (!((stack->array[e] >> k) & 1))
                    x *= -1;
                fprintf(output, "%" PRId64 " ", x);
    		}
    		fprintf(output, "0\n");
    	}
    }
}
