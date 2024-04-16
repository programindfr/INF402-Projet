#include <stdio.h>
#include <stdlib.h>
#include "listes.h"

#define DEBUG 1

sequence_t *regle2(int n)
{
	sequence_t *seq = malloc(sizeof(sequence_t));
	if (DEBUG && seq == NULL) {
		fprintf(stderr, "regle2: malloc sequence_t");
		exit(EXIT_FAILURE);
	}
	
	for (int i = 1; i <= (n - 2); i++) {
		for (int j = 1; j <= (n - 2); j++) {
			ajouter_sequence(0, '.', seq);
			ajouter_sequence(0, ')', seq);
			ajouter_sequence(0, '.', seq);
			ajouter_sequence(0, ')', seq);
			ajouter_sequence(0, '.', seq);
			
			ajouter_sequence(0, ')', seq);	// A
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(0, ')', seq);
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(-( (i+2)*n + j ), '\0', seq);	// -x(i+2,j) = -((i+2)*n + j)
			ajouter_sequence(-( (i+1)*n + j ), '\0', seq);	// -x(i+1,j) = -((i+1)*n + j)
			ajouter_sequence(0, '(', seq);
			ajouter_sequence(-( i*n + j ), '\0', seq);	// -x(i,j) = -(i*n + j)
			ajouter_sequence(0, '(', seq);	// !A
			
			ajouter_sequence(0, ')', seq);	// B
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(0, ')', seq);
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(0, '\0', seq);	// -x(i,j+2) = -((i)*n + j+2)
			ajouter_sequence(0, '\0', seq);	// TODO
			ajouter_sequence(0, '(', seq);
			ajouter_sequence(0, '\0', seq);	// TODO
			ajouter_sequence(0, '(', seq);	// !B
			
			ajouter_sequence(0, ')', seq);
			
			ajouter_sequence(0, ')', seq);	// C
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(0, ')', seq);
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(0, '\0', seq);	// TODO
			ajouter_sequence(0, '\0', seq);	// TODO
			ajouter_sequence(0, '(', seq);
			ajouter_sequence(0, '\0', seq);	// TODO
			ajouter_sequence(0, '(', seq);	// !C
			
			ajouter_sequence(0, ')', seq);
			
			ajouter_sequence(0, ')', seq);	// D
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(0, ')', seq);
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(0, '\0', seq);	// TODO
			ajouter_sequence(0, '\0', seq);	// TODO
			ajouter_sequence(0, '(', seq);
			ajouter_sequence(0, '\0', seq);	// TODO
			ajouter_sequence(0, '(', seq);	// !D
			
			ajouter_sequence(0, ')', seq);
		}
	}
}


int
main(int argc, char *argv[])
{
	return 0;
}
