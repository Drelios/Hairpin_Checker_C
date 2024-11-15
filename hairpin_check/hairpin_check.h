#ifndef HAIRPIN_CHECK_H
#define HAIRPIN_CHECK_H

// Function prototypes
int** create_matrix(int n);
void free_matrix(int** matrix, int n);
void traceback(int** matrix, char* sequence, char* dot_bracket, int i, int j, int (*is_valid_pair)(char, char));
void check_dot_bracket(char* dot_bracket, int threshold, int gap_authorized);
int** nussinov_jacobson(char* sequence, size_t n, int (*is_valid_pair)(char, char));
int is_valid_dna(char c1, char c2);
int is_valid_rna(char c1, char c2);
#endif
