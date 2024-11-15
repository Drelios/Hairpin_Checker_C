#include <stdio.h>
#include <stdlib.h>

char* FromFasta(char * fichier) {
    FILE* F = fopen(fichier, "r"); // Fix parameter order
    if (F == NULL) {
        fprintf(stderr, "Erreur ouverture fichier %s.\n", fichier);
        exit(EXIT_FAILURE);
    }

    fseek(F, 0, SEEK_END);
    long longueur = ftell(F);
    fseek(F, 0, SEEK_SET);

    char* seq = malloc(((size_t)longueur + 1) * sizeof(char)); // +1 pour stocker '\0'
    if (seq == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(F);
        exit(EXIT_FAILURE);
    }

    size_t bytesRead = fread(seq, (size_t)longueur, 1, F); // params : (Où_stock, taille du block, nombre de block,àpartir de quel fichier) --> un gros block
    if (bytesRead != 1) {
        fprintf(stderr, "Error reading file %s.\n", fichier);
        free(seq);
        fclose(F);
        exit(EXIT_FAILURE);
    }

    fclose(F);
    seq[longueur] = '\0';

    size_t read = 0, write = 0;
    while (seq[read] != '\n') {
        read++;
    }
    while (seq[read] != '\0') {
        if (seq[read] != '\n') {
            seq[write] = seq[read];
            ++write;
        }
        ++read;
    }
    seq[write] = '\0';
    ++write;
    seq = realloc(seq, write * sizeof(char));
    return seq;
}




