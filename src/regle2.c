#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include <regle2.h>

void
regle2_n(int64_t n, FILE *output)
{
	int64_t i, j, k;
	
	assert(n > 0 && n < 32 && (n & 1) == 0);
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (j < (n-2)) {
				// Génère les clauses pour les 3 variables consécutives dans la même ligne
				for (k = 0; k <= 2; k++)
					fprintf(output, "%" PRId64 " ", i*n + j+1+k);
				fprintf(output, "0\n");
				
				// Génère les clauses pour les négations des 3 variables consécutives dans la même ligne
				for (k = 0; k <= 2; k++)
					fprintf(output, "%" PRId64 " ", -i*n - (j+1+k));
				fprintf(output, "0\n");
			}
			
			if (i < (n-2)) {
				// Génère les clauses pour les 3 variables consécutives dans la même colonne
				for (k = 0; k <= 2; k++)
					fprintf(output, "%" PRId64 " ", (i+k)*n + j+1);
				fprintf(output, "0\n");
				
				// Génère les clauses pour les négations des 3 variables consécutives dans la même colonne
				for (k = 0; k <= 2; k++)
					fprintf(output, "%" PRId64 " ", -(i+k)*n - (j+1));
				fprintf(output, "0\n");
			}
		}
	}
}
