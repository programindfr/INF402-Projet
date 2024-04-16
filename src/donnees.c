#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "donnees.h"



cellule_t *nouvelle_cellule(void)
{
	return malloc(sizeof(cellule_t));
}


void ajouter_sequence(int val, char op, sequence_t *seq)
{
	cellule_t *suiv = seq->tete;
	
	seq->tete = nouvelle_cellule();
	seq->tete->val = val;
	seq->tete->op = op;
	seq->tete->suivant = suiv;
}


void afficher_sequence(sequence_t *seq)
{
    assert(seq);	// Le pointeur doit être valide
    cellule_t *cel = seq->tete;
    while (cel) {
    	if (cel->op)
    		printf("%c", cel->op);
    	else
    		printf("%d", cel->val);
    	cel = cel->suivant;
    }
}
