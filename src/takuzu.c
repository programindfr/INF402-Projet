#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "regle1.h"
#include "regle2.h"
#include "regle3.h"
#include "stack_t.h"

void
usage(char argv0[])
{
	fprintf(stderr, "Usage: %s n output-file\n", argv0);
}

int
main(int argc, char *argv[])
{
	int		s;
	int64_t	n, nVar, nClause;
	stack_t	stack;
	
	if (argc != 3) {				// 2 arguments: n et output-file
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	s = sscanf(argv[1], "%" PRId64, &n);
	if (s != 1) {					// Le premier argument doit etre un int64_t
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	assert(n < 32 && (n & 1) == 0);
	
	FILE *output = fopen(argv[2], "a");
	if (output == NULL) {			// Erreur d'ouverture du fichier
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	ensemble_create(&stack, n);
	
	nVar = n*n;
	nClause =
		stack_size(&stack)*2*n		// Nombre de clauses pour la regle 1
		+ (n-2)*(n-2)*4				// Nombre de clauses pour la regle 2
		+ 2*(n-1)*(1 << n);			// Nombre de clauses pour la regle 3
	
	fprintf(output, "p cnf %" PRId64 " %" PRId64 "\n", nVar, nClause);
	
	regle1_n(n, &stack, output);
	regle2_n(n, output);
	regle3_n(n, output);
	
	fclose(output);
	
	return 0;
}
