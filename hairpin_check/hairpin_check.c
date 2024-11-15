#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hairpin_check.h"

#define MAX_SEQ_LENGTH 1000



// Check for valid DNA pair
int is_valid_dna(char c1, char c2) {
    return (c1 == 'A' && c2 == 'T') || (c1 == 'T' && c2 == 'A') ||
           (c1 == 'G' && c2 == 'C') || (c1 == 'C' && c2 == 'G');
}

// Check for valid RNA pair
int is_valid_rna(char c1, char c2) {
    return (c1 == 'A' && c2 == 'U') || (c1 == 'U' && c2 == 'A') ||
           (c1 == 'G' && c2 == 'C') || (c1 == 'C' && c2 == 'G');
}


// Nussinov-Jacobson algorithm
int** nussinov_jacobson(char* sequence, size_t n, int (*is_valid_pair)(char, char)) {
    int** matrix = create_matrix(n);

    for (size_t length = 1; length < n; length++) {
        for (size_t i = 0; i < n - length; i++) {
            size_t j = i + length;

            // Case 1: Pairing between i and j
            if (is_valid_pair(sequence[i], sequence[j])) {
                matrix[i][j] = matrix[i + 1][j - 1] + 1;
            }

            // Case 2: Pairing between i and k, and between k+1 and j
            for (size_t k = i; k < j; k++) {
                if (matrix[i][j] < matrix[i][k] + matrix[k + 1][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k + 1][j];
                }
            }
        }
    }

    return matrix;
}

// Create a dynamic matrix
int** create_matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)calloc(n, sizeof(int));
    }
    return matrix;
}

// Free the dynamic matrix
void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Traceback to generate dot-bracket notation
void traceback(int** matrix, char* sequence, char* dot_bracket, int i, int j, int (*is_valid_pair)(char, char)) {
    if (i >= j) return;

    if (matrix[i][j] == matrix[i + 1][j - 1] + 1 && is_valid_pair(sequence[i], sequence[j])) {
        dot_bracket[i] = '(';
        dot_bracket[j] = ')';
        traceback(matrix, sequence, dot_bracket, i + 1, j - 1, is_valid_pair);
    } else {
        for (int k = i; k < j; k++) {
            if (matrix[i][j] == matrix[i][k] + matrix[k + 1][j]) {
                traceback(matrix, sequence, dot_bracket, i, k, is_valid_pair);
                traceback(matrix, sequence, dot_bracket, k + 1, j, is_valid_pair);
                break;
            }
        }
    }
}

// Check the dot-bracket notation
void check_dot_bracket(char* dot_bracket, int threshold, int gap_authorized) {
    int count = 0, gap_count = 0;
    for (int i = 0; dot_bracket[i] != '\0'; i++) {
        if (dot_bracket[i] == '(') {
            count++;
            if (count > threshold && gap_count <= gap_authorized) {
                printf("Hairpin structure: True\n");
                return;
            }
            gap_count = 0;
        } else if (dot_bracket[i] == ')') {
            count = 0;
            gap_count = 0;
        } else {
            if (count > 0 && count <= threshold) {
                gap_count++;
                if (gap_count > gap_authorized) {
                    count = 0;
                    gap_count = 0;
                }
            } else {
                count = 0;
                gap_count = 0;
            }
        }
    }
    printf("Hairpin structure: False\n");
}