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
	fprintf(stderr, "Usage: %s input-file output-file\n", argv0);
}

void
grid_alloc(int64_t *grid[], int64_t n)
{
	grid = malloc(sizeof(int64_t *) * n);
	for (int64_t i = 0; i < n; i++) {
		grid[i] = malloc(sizeof(int64_t) * n);
	}
}

void
grid_free(int64_t *grid[], int64_t n)
{
	for (int64_t i = 0; i < n; i++) {
		free(grid[i]);
	}
	free(grid);
}

int64_t
grid_fill(int64_t *grid[], int64_t n, FILE *input)
{
	char	c;
	int64_t	i, j, nFix;
	
	nFix = 0;
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(input, "%c", &c);
			switch (c) {
			case '0':
				grid[i][j] = -1;
				nFix++;
				break;
			
			case '1':
				grid[i][j] = 1;
				nFix++;
				break;
			
			default:
				grid[i][j] = 0;
				break;
			}
		}
		fscanf(input, "%c", &c);
	}
	
	return nFix;
}

void
grid_print(int64_t *grid[], int64_t n, FILE *output)
{
	int64_t	i, j;
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fprintf(output, "%" PRId64 "0\n", ((i-1)*n + j) * grid[i][j]);
		}
	}
}

int
main(int argc, char *argv[])
{
	int64_t	n, nVar, nClause, nFix;
	stack_t	stack;
	int64_t	**grid;
	
	grid = NULL;
	
	if (argc != 3) {				// 2 arguments: n et output-file
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	FILE *input = fopen(argv[1], "r");
	if (input == NULL) {			// Erreur d'ouverture du fichier
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	FILE *output = fopen(argv[2], "a");
	if (output == NULL) {			// Erreur d'ouverture du fichier
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if (fscanf(input, "%" PRId64 "\n", &n) != 1) {
		fprintf(stderr, "Erreur de lecture de la taille.\n");
		exit(EXIT_FAILURE);
	}
	
	assert(n < 32 && (n & 1) == 0);
	
	grid_alloc(grid, n);
	nFix = grid_fill(grid, n, input);
	
	ensemble_create(&stack, n);
	nVar = n*n;
	nClause =
		nFix						// Nombre de variables fixes
		+ stack_size(&stack)*2*n	// Nombre de clauses pour la regle 1
		+ (n-2)*(n-2)*4				// Nombre de clauses pour la regle 2
		+ 2*(n-1)*(1 << n);			// Nombre de clauses pour la regle 3
	
	fprintf(output, "p cnf %" PRId64 " %" PRId64 "\n", nVar, nClause);
	regle1_n(n, &stack, output);
	regle2_n(n, output);
	regle3_n(n, output);
	grid_print(grid, n, output);
	
	fclose(output);
	grid_free(grid, n);
	
	return 0;
}
