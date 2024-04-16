#include <stdio.h>
#include "../src/donnees.h"
#include "../src/logique.h"



int
main(int argc, char *argv[])
{
	/*printf("Règle 1: ");
	sequence_t *r1 = regle1(2);
	afficher_sequence(r1);*/
	
	printf("\nRègle 2: ");
	sequence_t *r2 = regle2(2);
	afficher_sequence(r2);	// affiche rien pour n=2, c'est normale
	
	printf("\nRègle 3: ");
	sequence_t *r3 = regle3(2);
	afficher_sequence(r3);
	
	return 0;
}
