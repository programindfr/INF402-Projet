#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <regle1.h>
#include <regle2.h>
#include <regle3.h>
#include <stack_t.h>

void
usage(char argv0[])
{
	fprintf(stderr, "Usage: %s input-file\n", argv0);
}

int64_t **
grid_alloc(int64_t n)
{
	int64_t i;
	int64_t **grid;
	
	grid = malloc(sizeof(int64_t *) * n);
	
	for (i = 0; i < n; i++)
		grid[i] = malloc(sizeof(int64_t) * n);
	
	return grid;
}

void
grid_free(int64_t *grid[], int64_t n)
{
	assert(grid != NULL);
	
	int64_t i;
	
	for (i = 0; i < n; i++)
		free(grid[i]);
	
	free(grid);
}

int64_t
grid_fill(int64_t *grid[], int64_t n, FILE *input)
{
	assert(grid != NULL);
	
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
	assert(grid != NULL);
	
	int64_t	i, j;
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (grid[i][j] != 0)
				fprintf(output, "%" PRId64 " 0\n", (i*n + j+1) * grid[i][j]);
		}
	}
}

void
dimacs_to_takuzu(FILE *input, FILE *output, int64_t *grid[], int64_t n)
{
	assert(grid != NULL);
	
	char	header[8];
	int64_t	i, j, var;
	
	fprintf(output, "%" PRId64 "\n", n);
	fscanf(input, "%s\n", header);
		
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (header[0] == 'S')
				fscanf(input, "%" PRId64 " ", &var);
			else
				var = grid[i][j];
			
			if (var < 0)
				fprintf(output, "0");
			else if (var > 0)
				fprintf(output, "1");
			else
				fprintf(output, "#");
		}
		fprintf(output, "\n");
	}
}

int
main(int argc, char *argv[])
{
	char		satExec[256], file[256];
	int64_t		n, nVar, nFix;
	int64_t		**grid;
	stack_t		stack;
	uint64_t	nClause;
	
	if (argc != 2) {				// 1 argument: input-file
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	snprintf(file, 256, "%s.takuzu", argv[1]);
	FILE *inputTakuzu = fopen(file, "r");
	if (inputTakuzu == NULL) {			// Erreur d'ouverture du fichier
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	snprintf(file, 256, "%s.dimacs", argv[1]);
	FILE *outputDimacs = fopen(file, "w");
	if (outputDimacs == NULL) {			// Erreur d'ouverture du fichier
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	if (fscanf(inputTakuzu, "%" PRId64 "\n", &n) != 1) {
		fprintf(stderr, "Erreur de lecture de la taille.\n");
		exit(EXIT_FAILURE);
	}
	
	assert(n > 0 && n < 32 && (n & 1) == 0);
	
	grid = grid_alloc(n);
	nFix = grid_fill(grid, n, inputTakuzu);
	
	ensemble_create(&stack, n);
	nVar = n*n;
	nClause =
		nFix							// Nombre de variables fixes
		+ stack_size(&stack)*2*n		// Nombre de clauses pour la regle 1
		+ (n-2)*n*4						// Nombre de clauses pour la regle 2
		+ n*(n-1)*(1 << n);				// Nombre de clauses pour la regle 3; 2 * ( n*(n-1) / 2 ) * (1 << 2)
	
	fprintf(outputDimacs, "p cnf %" PRId64 " %" PRIu64 "\n", nVar, nClause);
	regle1_n(n, &stack, outputDimacs);
	regle2_n(n, outputDimacs);
	regle3_n(n, outputDimacs);
	grid_print(grid, n, outputDimacs);
	
	stack_free(&stack);
	fclose(inputTakuzu);
	fclose(outputDimacs);
	
	snprintf(satExec, 256, "minisat %s.dimacs %s_sol.dimacs", argv[1], argv[1]);
	system(satExec);
	
	snprintf(file, 256, "%s_sol.takuzu", argv[1]);
	FILE *outputTakuzu = fopen(file, "w");
	if (outputTakuzu == NULL) {			// Erreur d'ouverture du fichier
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	snprintf(file, 256, "%s_sol.dimacs", argv[1]);
	FILE *inputDimacs = fopen(file, "r");
	if (inputDimacs == NULL) {			// Erreur d'ouverture du fichier
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}
	
	dimacs_to_takuzu(inputDimacs, outputTakuzu, grid, n);
	
	fclose(inputDimacs);
	fclose(outputTakuzu);
	grid_free(grid, n);
	
	return 0;
}
