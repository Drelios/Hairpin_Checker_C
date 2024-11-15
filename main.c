#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./hairpin_check/hairpin_check.h"
#include "./FASTA/FASTA.h"

#define MAX_SEQ_LENGTH 1000

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <type_file> <sequence_file>\n", argv[0]);
        return 1;
    }

    
    char* type = (argv[1]);
    char* sequence = FromFasta(argv[2]);

    if (!type || !sequence) {
        fprintf(stderr, "Error: Failed to read type or sequence from FASTA files.\n");
        free(type);
        free(sequence);
        return 1;
    }

    // Convert type to uppercase
    for (size_t i = 0; i < strlen(type); i++) {
        type[i] = (char)toupper(type[i]);
    }

    // Convert sequence to uppercase
    for (size_t i = 0; i < strlen(sequence); i++) {
        sequence[i] = (char)toupper(sequence[i]);
    }

    size_t n = strlen(sequence);
    int** result_matrix;
    int (*is_valid_pair)(char, char) = NULL;

    // Validate type and sequence
    if (strcmp(type, "DNA") == 0) {
        for (size_t i = 0; i < n; i++) {
            if (strchr("ATGC", sequence[i]) == NULL) {
                fprintf(stderr, "Error: Invalid character '%c' in DNA sequence.\n", sequence[i]);
                free(type);
                free(sequence);
                return 1;
            }
        }
        is_valid_pair = is_valid_dna;
    } else if (strcmp(type, "RNA") == 0) {
        for (size_t i = 0; i < n; i++) {
            if (strchr("AUGC", sequence[i]) == NULL) {
                fprintf(stderr, "Error: Invalid character '%c' in RNA sequence.\n", sequence[i]);
                free(type);
                free(sequence);
                return 1;
            }
        }
        is_valid_pair = is_valid_rna;
    } else {
        fprintf(stderr, "Error: Sequence type must be DNA or RNA.\n");
        free(type);
        free(sequence);
        return 1;
    }

    // Run Nussinov-Jacobson algorithm
    result_matrix = nussinov_jacobson(sequence, n, is_valid_pair);

    // Generate dot-bracket notation
    char dot_bracket[MAX_SEQ_LENGTH];
    memset(dot_bracket, '.', sizeof(dot_bracket));
    dot_bracket[n] = '\0';

    traceback(result_matrix, sequence, dot_bracket, 0, n - 1, is_valid_pair);

    printf("The most likely hairpin scheme is %s.\n", dot_bracket);

    // Check hairpin structure
    check_dot_bracket(dot_bracket, 5, 2);  // Threshold = 5, Gap = 2

    // Free dynamically allocated memory
    free_matrix(result_matrix, n);
    //free(type);
    free(sequence);

    return 0;
}
