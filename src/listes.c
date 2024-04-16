#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"

bool silent_mode = false;

cellule_t* nouvelle_cellule(void)
{
	return malloc(sizeof(cellule_t));
}


void detruireCellule(cellule_t* cel)
{
    free(cel);
}


void detruireSequence(sequence_t* seq)
{
	cellule_t *cel = seq->tete;
	cellule_t *suiv = NULL;
	while (cel->suivant != NULL)
	{
		suiv = cel->suivant;
		detruireCellule(cel);
		cel = suiv;
	}
	detruireCellule(cel);
}


void conversion(char *texte, sequence_t *seq)
{
	cellule_t *cel;
	if (texte[0]) {
		seq->tete = nouvelleCellule();
		seq->tete->command = texte[0];
		cel = seq->tete;
		for (int i = 1; texte[i]; i++) {
			cel->suivant = nouvelleCellule();
			cel = cel->suivant;
			cel->command = texte[i];
		}
		cel->suivant = NULL;
	} else {
		seq->tete = NULL;
	}
}


void ajouter_sequence(int val, char op, sequence_t *seq)
{
	cellule_t *suiv = seq->tete;
	
	seq->tete = nouvelle_cellule();
	seq->tete->val = val;
	seq->tete->op = op;
	seq->tete->suivant = suiv;
}


void afficher(sequence_t* seq)
{
    assert(seq); /* Le pointeur doit être valide */
    cellule_t *cel = seq->tete;
    while (cel) {
    	printf("%c", cel->command);
    	cel = cel->suivant;
    }
}


bool prendreTete(sequence_t* seq, char *c)
{
	// assert(seq); /* Le pointeur doit être valide */
	if (seq == NULL)
		return false;
	*c = seq->tete->command;
	cellule_t *cel = seq->tete->suivant;
	detruireCellule(seq->tete);
	seq->tete = cel;
	return true;
}

// Ajout pile
void creer_pile(pile_t *p)
{
	p->max = N_MAX_PILE;
	p->n = 0;
	p->tab = malloc(sizeof(pile_elem) * p->max);
}

int est_vide(pile_t *p) { return p->n == 0; }

char* sommet(pile_t *p, int *x)
{
	*x = p->tab[p->n-1].x;
	return p->tab[p->n-1].c;
}

int taille(pile_t *p) { return p->n; }

void print(pile_t *p) {
	for (int i = 0; i < p->n; i++)
	{
		if (p->tab[i].c != NULL)
			printf("%s\n", p->tab[i].c);
		else
			printf("%d\n", p->tab[i].x);
	}
}

void vider(pile_t *p)
{
	for (int i = 0; i < p->n; i++)
	{
		if (p->tab[i].c != NULL)
			free(p->tab[i].c);
	}
	free(p->tab);
	creer_pile(p);
}

void empiler(pile_t *p, int x, char *c)
{
	if (p->n >= p->max)
	{
		p->max *= 2;
		p->tab = realloc(p->tab, sizeof(pile_elem) * p->max);
	}
	p->tab[p->n].x = x;
	p->tab[p->n].c = c;
	p->n++;
}

void empilerInt(pile_t *p, int x)
{
	empiler(p, x, NULL);
}

void empilerChar(pile_t *p, char *c)
{
	empiler(p, 0, c);
}

char* depiler(pile_t *p, int *x)
{
	p->n--;
	*x = p->tab[p->n].x;
	return p->tab[p->n].c;
}

int depilerInt(pile_t *p)
{
	int x;
	char *c = depiler(p, &x);
	assert(c == NULL);
	return x;
}

char* depilerChar(pile_t *p)
{
	int x;
	char *c = depiler(p, &x);
	assert(c != NULL);
	return c;
}
