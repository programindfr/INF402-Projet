#ifndef __LISTES_H__
#define __LISTES_H__

#include <stdbool.h>

#ifdef SILENT

#define printf(fmt, ...) (0)
#define eprintf(fmt, ...) (0)
#define putchar(c) (0)

#else

#define eprintf(...) fprintf (stderr, __VA_ARGS__)

#endif

extern bool silent_mode;

struct cellule {
	int		val;	// variable booleen pour sat solver
	char	op;		// operateur
    struct	cellule *suivant;
};
typedef struct cellule cellule_t;

struct sequence {
    cellule_t *tete;
};
typedef struct sequence sequence_t;

cellule_t* nouvelleCellule (void);

void detruireCellule (cellule_t*);
void detruireSequence (sequence_t* seq);

void conversion (char *texte, sequence_t *seq);
void conversionTete(char *texte, sequence_t *seq);

void afficher (sequence_t* seq);

bool prendreTete(sequence_t* seq, char *c);

#define N_MAX_PILE 1

typedef struct {
	int x;
	char *c;
} pile_elem;

struct pile {
	int max;
	int n;
	pile_elem *tab;
};
typedef struct pile pile_t;

void creer_pile(pile_t *p);
int est_vide(pile_t *p);
char* sommet(pile_t *p, int *x);
int taille(pile_t *p);
void print(pile_t *p);

void vider(pile_t *p);
void empiler(pile_t *p, int x, char *c);
void empilerInt(pile_t *p, int x);
void empilerChar(pile_t *p, char *c);
char* depiler(pile_t *p, int *x);
int depilerInt(pile_t *p);
char* depilerChar(pile_t *p);

#endif
