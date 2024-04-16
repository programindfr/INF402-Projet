#include <stdio.h>
#include <stdlib.h>
#include "donnees.h"
#include "logique.h"

#define DEBUG 1	//TODO: initialiser depuis le makefile



/*sequence_t *regle1(int n)
{
    sequence_t *seq = malloc(sizeof(sequence_t));
    if (DEBUG && seq == NULL) {
        fprintf(stderr, "regle1: malloc sequence_t");
        exit(EXIT_FAILURE);
    }

    //recup l'ensemble du tab de taill emax

    //neg tout
        ajouter_sequence(0, '+', seq);
    ajouter_sequence(0, ')', seq);
    for (int i = 1; i <= TAILLEMAX; i++) {                     //parcours tableau
                ajouter_sequence(0, '+', seq);
            ajouter_sequence(0, ')', seq);
        for (int j = 1; j <=TAILLEMAX; j++) {
                        ajouter_sequence(0, '+', seq);

            ajouter_sequence(0, ')', seq);            //optinelle?
            ajouter_sequence(tab[i][j], '\0', seq);   //tab[i][j] à supposer que dans le tableau , les éléments sont deja sous la forme voulu.

                        ajouter_sequence(0, '(', seq);            //optinelle?
        }
                ajouter_sequence(0, '(', seq);
    }
        ajouter_sequence(0, '(', seq);
}*/


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
			
			ajouter_sequence(0, ')', seq);					// A
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(0, ')', seq);
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(-((i+2)*n + j), '\0', seq);	// -x(i+2,j) = -((i+2)*n + j)
			ajouter_sequence(-((i+1)*n + j), '\0', seq);	// -x(i+1,j) = -((i+1)*n + j)
			ajouter_sequence(0, '(', seq);
			ajouter_sequence(-(i*n + j), '\0', seq);		// -x(i,j) = -(i*n + j)
			ajouter_sequence(0, '(', seq);					// !A
			
			ajouter_sequence(0, ')', seq);					// B
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(0, ')', seq);
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(-(i*n + j+2), '\0', seq);		// -x(i,j+2) = -(i*n + j+2)
			ajouter_sequence(-(i*n + j+1), '\0', seq);		// -x(i,j+1) = -(i*n + j+1)
			ajouter_sequence(0, '(', seq);
			ajouter_sequence(-(i*n + j), '\0', seq);		// -x(i,j) = -(i*n + j)
			ajouter_sequence(0, '(', seq);					// !B
			
			ajouter_sequence(0, ')', seq);
			
			ajouter_sequence(0, ')', seq);					// C
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(0, ')', seq);
			ajouter_sequence(0, '+', seq);
			ajouter_sequence((i+2)*n + j, '\0', seq);		// x(i+2,j) = (i+2)*n + j
			ajouter_sequence((i+1)*n + j, '\0', seq);		// x(i+1,j) = (i+1)*n + j
			ajouter_sequence(0, '(', seq);
			ajouter_sequence(i*n + j, '\0', seq);			// x(i,j) = i*n + j
			ajouter_sequence(0, '(', seq);					// !C
			
			ajouter_sequence(0, ')', seq);
			
			ajouter_sequence(0, ')', seq);					// D
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(0, ')', seq);
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(i*n + j+2, '\0', seq);			// x(i,j+2) = i*n + j+2
			ajouter_sequence(i*n + j+1, '\0', seq);			// x(i,j+1) = i*n + j+1
			ajouter_sequence(0, '(', seq);
			ajouter_sequence(i*n + j, '\0', seq);			// x(i,j) = i*n + j
			ajouter_sequence(0, '(', seq);					// !D
			
			ajouter_sequence(0, ')', seq);
		}
	}
	
	return seq;
}


sequence_t *regle3(int n)
{
    sequence_t *seq = malloc(sizeof(sequence_t));
    if (DEBUG && seq == NULL) {
        fprintf(stderr, "regle3: malloc sequence_t");
        exit(EXIT_FAILURE);
    }

    // négationner tout ca 
    ajouter_sequence(0, '+', seq);
    ajouter_sequence(0, ')', seq);
    
    for (int j = 2; j <= n; j++) {						// somme
    	if (j != 2) ajouter_sequence(0, ')', seq);
    	if (j != n) {
			ajouter_sequence(0, '+', seq);
			ajouter_sequence(0, ')', seq);
    	}
        for (int i = 1; i <= n; i++) {					// produit
            ajouter_sequence(0, '+', seq);
            ajouter_sequence(0, ')', seq);

            ajouter_sequence(0, '.', seq);
            ajouter_sequence(0, ')', seq);
            ajouter_sequence(-(i*n + j), '\0', seq); 	// -x(i,j) = -(i*n + j)
            ajouter_sequence(0, '(', seq);
            ajouter_sequence(0, ')', seq);
            ajouter_sequence(-(i*n + 1), '\0', seq); 	// -x(i,1) = -(i*n + 1)
            ajouter_sequence(0, '(', seq);

            ajouter_sequence(0, '(', seq);


            ajouter_sequence(0, ')', seq);

            ajouter_sequence(0, '.', seq);
            ajouter_sequence(i*n + j, '\0', seq);		// x(i,j) = i*n + j
            ajouter_sequence(i*n + 1, '\0', seq);		// x(i,1) = i*n + 1

            ajouter_sequence(0, '(', seq);
        }
        ajouter_sequence(0, '(', seq);
    }
    for (int j = 2; j <= n; j++) ajouter_sequence(0, '(', seq); // TODO: nb iterations ?
    ajouter_sequence(0, '(', seq);
    ajouter_sequence(0, '(', seq);

    ajouter_sequence(0, ')', seq);
    for (int j = 2; j <= n; j++) {						// somme
        for (int i = 1; i <= n; i++) {					// produit
            ajouter_sequence(0, '+', seq);

            ajouter_sequence(0, ')', seq);

            ajouter_sequence(0, '.', seq);
            ajouter_sequence(-(i*n + j), '\0', seq);	// -x(i,j) = -(i*n + j)
            ajouter_sequence(-(n + j), '\0', seq);		// -x(1,j) = -(n + j)

            ajouter_sequence(0, '(', seq);


            ajouter_sequence(0, ')', seq);

            ajouter_sequence(0, '.', seq);
            ajouter_sequence(i*n + j, '\0', seq); 		// x(i,j) = i*n + j
            ajouter_sequence(n + j, '\0', seq); 		// x(1,j) = n + j

            ajouter_sequence(0, '(', seq);
        }
    }
    ajouter_sequence(0, '(', seq);
    
    return seq;
}
