
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

#include <regle1.h>
#include <regle2.h>
#include <regle3.h>
#include <stack_t.h>

int main() {
    int n;
    FILE *output;
    stack_t stack;

    // Test de la règle 1 pour n = 2 et n = 4
    for (n = 2; n <= 4; n += 2) {
        char filename[256];
        snprintf(filename, sizeof(filename), "test_regle1_%d.txt", n);
        output = fopen(filename, "w");
        assert(output != NULL);
        ensemble_create(&stack, n);
        regle1_n(n, &stack, output);
        fclose(output);
    }

    // Test de la règle 2 pour n = 4
    n = 4;
    output = fopen("test_regle2_4.txt", "w");
    assert(output != NULL);
    regle2_n(n, output);
    fclose(output);

    // Test de la règle 3 pour n = 2 et n = 4
    for (n = 2; n <= 4; n += 2) {
        char filename[256];
        snprintf(filename, sizeof(filename), "test_regle3_%d.txt", n);
        output = fopen(filename, "w");
        assert(output != NULL);
        regle3_n(n, output);
        fclose(output);
    }

    // Comparaison des fichiers de sortie avec les fichiers de test fournis
    system("diff -s test_regle1_2.txt test_regle1_2_fourni.txt");
    system("diff -s test_regle1_4.txt test_regle1_4_fourni.txt");
    system("diff -s test_regle2_4.txt test_regle2_4_fourni.txt");
    system("diff -s test_regle3_2.txt test_regle3_2_fourni.txt");
    system("diff -s test_regle3_4.txt test_regle3_4_fourni.txt");

    return 0;
}

