#ifndef __DONNEES_H__
#define __DONNEES_H__



// structures
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



// fonctions
cellule_t *nouvelleCellule(void);
void ajouter_sequence(int val, char op, sequence_t *seq);
void afficher_sequence(sequence_t *seq);



#endif//__DONNEES_H__
