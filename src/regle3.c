#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include <regle3.h>

void
regle3_n(int64_t n, FILE *output)
{
	int64_t i1, j1, i, j, k, x1, x2;
	int64_t imax = 1 << n;
	int64_t jmax = 1 << n;
	
	assert(n > 0 && n < 32 && (n & 1) == 0);
	
	// Génère les clauses pour les paires (x1, x2) où x1 et x2 sont des variables
	// booléennes représentant les valeurs de vérité des propositions logiques.
	// Les paires sont générées pour chaque paire de colonnes (j1, k) où j1 < k.
	for (j1 = 0; j1 < (n-1); j1++) {				//parcours des colonnes pour comparer j1 et k (allant de 0 à n-1)
		for (k = (j1+1); k < n; k++) {				//parcours des colonnes pour comparer j1 et k (allant de 1 à n )
			for (j = 0; j < jmax; j++) {			//parcours des combinaisons de valeurs pour les colonnes
				for (i = 0; i < n; i++) {			//parcours des element d'une colonne
					x1 = i*n + j1+1;
					x2 = i*n + k+1;
					if (!((j >> (n-i-1)) & 1)) {
						x1 *= -1;
						x2 *= -1;
					}
					fprintf(output, "%" PRId64 " %" PRId64 " ", x1, x2);
				}
				fprintf(output, "0\n");
			}
		}
	}
	
	// Génère les clauses pour les paires (x1, x2) où x1 et x2 sont des variables
	// booléennes représentant les valeurs de vérité des propositions logiques.
	// Les paires sont générées pour chaque paire de lignes (i1, k) où i1 < k.
	for (i1 = 0; i1 < (n-1); i1++) {				//parcours des lignes pour comparer i1 et k (allant de 0 à n-1)
		for (k = (i1+1); k < n; k++) {				//parcours des lignes pour comparer i1 et k (allant de 1 à n )
			for (i = 0; i < imax; i++) {			//parcours des combinaisons de valeurs pour les lignes
				for (j = 0; j < n; j++) {			//parcours des elements d'une ligne
					x1 = i1*n + j+1;
					x2 = k*n + j+1;
					if (!((i >> (n-j-1)) & 1)) {
						x1 *= -1;
						x2 *= -1;
					}
					fprintf(output, "%" PRId64 " %" PRId64 " ", x1, x2);
				}
				fprintf(output, "0\n");
			}
		}
	}
}
