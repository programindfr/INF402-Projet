#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#ifdef NCURSES
#include <ncurses.h>
#endif
#include "listes.h"
#include "curiosity.h"
#include <string.h>

void stop(void)
{
    char enter = '\0';
    printf ("Appuyer sur entrée pour continuer...\n");
    while (enter != '\r' && enter != '\n') { enter = getchar(); }
}

int interprete(sequence_t* seq, bool debug)
{
    char commande;
    int a, b, c;
    char *ca = NULL;
    char *cb = NULL;
    char *cc = NULL;
	pile_t *pile = malloc(sizeof(pile_t));
	creer_pile(pile);

    printf ("Programme:");
    afficher(seq);
    printf ("\n");
    if (debug) stop();

    int ret;

    while (prendreTete(seq, &commande)) {
        switch (commande) {
            case 'A':
                ret = avance();
                if (ret == VICTOIRE)
                {
                	vider(pile);
                	free(pile->tab);
                	free(pile);
                	detruireSequence(seq);
                	return VICTOIRE; /* on a atteint la cible */
                }
                if (ret == RATE)
                {
                	vider(pile);
                	free(pile->tab);
                	free(pile);
                	detruireSequence(seq);
                	return RATE;     /* tombé dans l'eau ou sur un rocher */
                }
                break;
            
            case 'D':
                droite();
                break;
            
            case 'G':
                gauche();
                break;
            
            case 'M':
            	ca = depiler(pile, &a);
            	if (debug) assert(ca == NULL);	// Mesure sur un char* !
        		b = mesure(a);
            	empilerInt(pile, b);
                break;
            
            case 'P':
            	ca = depiler(pile, &a);
            	if (debug) assert(ca == NULL);	// Pose sur un char* !
                pose(a);
                break;
			
			case '0' ... '9':
				empilerInt(pile, commande - 48);
				break;
			
			case '+':
				ca = depiler(pile, &a);
				cb = depiler(pile, &b);
				if (debug) assert(ca == NULL && cb == NULL);	// + sur un char* !
				empilerInt(pile, (b + a));
				break;
			
			case '-':
				ca = depiler(pile, &a);
				cb = depiler(pile, &b);
				if (debug) assert(ca == NULL && cb == NULL);	// - sur un char* !
				empilerInt(pile, (b - a));
				break;
			
			case '*':
				ca = depiler(pile, &a);
				cb = depiler(pile, &b);
				if (debug) assert(ca == NULL && cb == NULL);	// * sur un char* !
				empilerInt(pile, (b * a));
				break;
			
			case '/':
				ca = depiler(pile, &a);
				cb = depiler(pile, &b);
				if (debug) assert(ca == NULL && cb == NULL);	// / sur un char* !
				empilerInt(pile, (b / a));
				break;
			
			case '{':
				prendreTete(seq, &commande);
				int sizeca = 1;
				ca = malloc(sizeof(char) * sizeca);
				int i;
				int flag = true;
				int count = 0;
				for (i = 0; flag; i++)
				{
					if (commande == '}' && count == 0)
						flag = false;
					else
					{
						if (commande == '{')
							count++;
						else if (commande == '}' && count > 0)
							count--;
						if (i >= sizeca)
						{
							sizeca *= 2;
							ca = realloc(ca, sizeof(char) * sizeca);
						}
						ca[i] = commande;
						prendreTete(seq, &commande);
					}
				}
				ca[i-1] = '\0';
				empilerChar(pile, ca);
				break;
			
			case '?':
				ca = depiler(pile, &a);	// F
				cb = depiler(pile, &b);	// V
				cc = depiler(pile, &c);	// n
				if (debug) assert(ca != NULL && cb != NULL && cc == NULL);
				if (c == 0)
					conversionTete(ca, seq);
				else
					conversionTete(cb, seq);
				free(ca);
				free(cb);
				break;
			
			case '!':
				ca = depiler(pile, &a);	// e
				if (debug) assert(ca != NULL);	// Pas d'execution d'entiers
				conversionTete(ca, seq);
				free(ca);
				break;
			
			case 'X':
				ca = depiler(pile, &a);	// a
				cb = depiler(pile, &b);	// b
				empiler(pile, a, ca);
				empiler(pile, b, cb);
				break;
			
			case 'C':
				ca = depiler(pile, &a);	// e
				if (ca == NULL)
				{
					empilerInt(pile, a);
					empilerInt(pile, a);
				}
				else
				{
					empilerChar(pile, ca);
					int size = strlen(ca);
					cb = malloc(sizeof(char) * size);
					strcpy(cb, ca);
					empilerChar(pile, cb);
				}
				break;
			
			case 'I':
				ca = depiler(pile, &a);	// e
				if (ca != NULL)
					free(ca);
				break;
			
			case 'B':
				ca = depiler(pile, &a);	// n
				cb = depiler(pile, &b);	// cmd
				if (debug) assert(ca == NULL && cb != NULL);	// a == int && cb == char*
				if (a > 0)
				{
					conversionTete("B", seq);
					conversionTete(cb, seq);
					empilerChar(pile, cb);
					empilerInt(pile, a - 1);
				}
				else
					free(cb);
				break;
			
			case 'R':
				ca = depiler(pile, &a);	// x
				cb = depiler(pile, &b);	// n
				if (debug) assert(ca == NULL && cb == NULL);	// x et n entiers
				for (int j = 0; j < a; j++)
				{
					pile_elem e = pile->tab[pile->n - b];
					for (int i = pile->n - b + 1; i < pile->n; i++)
					{
						pile->tab[i - 1] = pile->tab[i];
					}
					pile->tab[pile->n - 1] = e;
				}
				break;
			
			case 'Z':
				for (int j = 0; j < taille(pile) / 2; j++)
				{
					pile_elem e = pile->tab[j];
					pile->tab[j] = pile->tab[pile->n - j - 1];
					pile->tab[pile->n - j - 1] = e;
				}
				break;

            default:
                if (debug) eprintf("Caractère inconnu: '%c'\n", commande);
        }

        /* Affichage pour faciliter le debug */
        afficherCarte();
        printf ("Programme:");
        afficher(seq);
        printf ("\n");
        print(pile);
        if (debug) stop();
    }

    /* Si on sort de la boucle sans arriver sur la cible,
     * c'est raté :-( */

	vider(pile);
	free(pile->tab);
	free(pile);
	detruireSequence(seq);
    return CIBLERATEE;
}
