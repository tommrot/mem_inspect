#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "take_data.h"


void take_expression(char *type, char *operation, char *value1, char *value2){
    printf("operator 1:\n");
    take_data(type, value1);
    printf("operation: %s\n", operation);
    printf("operator 2:\n");
    take_data(type, value2);
    printf("result is:\n");
    if (strcmp(type, "int") == 0){
        int result = 0;
        if (strcmp(operation, "add") == 0) result = atoi(value1) + atoi(value2);
        else if (strcmp(operation, "sub") == 0) result = atoi(value1) - atoi(value2);
        else if (strcmp(operation, "mul") == 0) result = atoi(value1) * atoi(value2);
        else if (strcmp(operation, "div") == 0) result = atoi(value1) / atoi(value2);
        print_bits("int", &result);
        print_hex(type, &result);
    } else if (strcmp(type, "float") == 0){
        float result = atof(value1) + atof(value2);
        print_float(&result);
        print_hex(type, &result);
    }
}





