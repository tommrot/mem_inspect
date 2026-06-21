#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void take_arr(char **argv){
    int num_of_elements = atoi(argv[3]);
    void *p = NULL;
    size_t size = 0;
    if (strcmp(argv[1], "int") == 0 || strcmp(argv[1], "float") == 0) size = sizeof(int); 
    else if (strcmp(argv[1], "char") == 0) size = sizeof(char);
    else if (strcmp(argv[1], "string") == 0) size = sizeof(p);

    p = malloc(size * num_of_elements);
    if (p == NULL) return;
    for (int i = 0; i < num_of_elements; i++){
        if (strcmp(argv[1], "int") == 0){
            ((int *)p)[i] = atoi(argv[4 + i]);
        } else if (strcmp(argv[1], "float") == 0){
            ((float *)p)[i] = atof(argv[4 + i]);
        } else if (strcmp(argv[1], "char") == 0){
            ((char*)p)[i] = *(argv[4 + i]);
        } else if (strcmp(argv[1], "string") == 0){
            char *word = malloc(strlen(argv[4 + i]) + 1);
            strcpy(word, argv[4 + i]);
            ((char **)p)[i] = word;
        }
    }
    for (int i = num_of_elements - 1; i >= 0; i--){
        for (int j = size - 1; j >= 0; j--){
            for (int k = 7; k >= 0; k--){
                int bit = (((char*)p)[i * size + j] >> k) & 1;
                printf("%d", bit);
            }
            printf(" ");
        }
        printf("\n");
    }
    free(p);
}