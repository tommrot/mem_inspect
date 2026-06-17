#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void print_bits(char *type, void *value);
void print_float(float *value);
void print_hex(char *type, void *value);
void print_addresses(char *type, void *value);

void take_data(char *type, char* value){
    void *data_p = NULL;
    if (strcmp(type, "int") == 0){
        data_p = malloc(sizeof(int));
        *((int*)data_p) = atoi(value);
    } else if (strcmp(type, "float") == 0){
        data_p = malloc(sizeof(float));
        *((float*)data_p) = atof(value);
    } else if (strcmp(type, "char") == 0){
        data_p = malloc(sizeof(char));
        *((char*) data_p) = *value;
    } else if (strcmp(type, "string") == 0){
        data_p = malloc(sizeof(char) * strlen(value) + 1);
        strcpy((char*)data_p, value);
    }

    if (strcmp(type, "float") != 0) print_bits(type, data_p);
    else print_float(data_p);
    print_hex(type, data_p);
    print_addresses(type, data_p);
}



void print_bits(char *type , void* value){
    char *p = (char*)value;
    if (strcmp(type, "int") == 0){
        size_t size = sizeof(int);
        for (int i = (int)size - 1; i >= 0; i--){
            for (int j = 7; j >= 0; j--){
                int bit = (p[i] >> j) & 1;
                printf("%d", bit);
            }
            printf("\n");
        }

    }else if (strcmp(type, "char") == 0){
        for (int i = 7; i >= 0; i--){
            int bit = (*p >> i) & 1;
            printf("%d", bit);
        }
        printf("\n");
    } 
    else if (strcmp(type, "string") == 0){
        size_t size = sizeof(char) * strlen(value);
        for (int i = (int)size - 1; i >= 0; i--){
            for (int j = 7; j >= 0; j--){
                int bit = (p[i] >> j) & 1;
                printf("%d", bit);
            } 
            printf("\n");
        }
    }
}


void print_float(float *value){
    unsigned int *p = (unsigned int*)value;  //casting pointers doesn't modify internal bits, casting float to integer or vice versa yes, but not pointers
    for (int i = 31; i >= 0; i--){
        int bit = (*p >> i) & 1;
        if (i == 31) printf("sign bit: %d\nexponent bits: ", bit);
        else if (i <= 30 && i >= 23) {
            printf("%d", bit);
            if (i == 23) printf("\nmantix bits: ");
        } else {
            printf("%d", bit);
        }
    }
    printf("\n");
}

void print_hex(char *type, void* value){
    size_t size = 0;
    unsigned char *p = (unsigned char *) value;
    if (strcmp(type, "int") == 0 || strcmp(type, "float") == 0) size = sizeof(int);
    else if (strcmp(type, "char") == 0) size = sizeof(char);
    else if (strcmp(type, "string") == 0) size = strlen((char*)value);

    printf("hexadecimal:\n");
    for (int i = (int)size - 1; i >= 0; i--){
        printf("%02x", p[i]);    
    }
    printf("\n");
}

void print_addresses(char *type, void *value){
    char *p = (char*) value;
    size_t size = 0;
    if (strcmp(type, "int") == 0 || strcmp(type, "float") == 0) size = sizeof(int);
    else if (strcmp(type, "char") == 0) size = sizeof(char);
    else if (strcmp(type, "string") == 0) size = sizeof(char) * strlen(value);
    for (int i = (int) size - 1; i >= 0; i--){
        printf("%p\n", p + i);
    }
}