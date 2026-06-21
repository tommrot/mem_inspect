#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "take_data.h"
#include "compute_datas.h"
#include "take_arr.h"


int main(int argc, char **argv){
    if (argc < 2) return EXIT_FAILURE;
    if (argc < 5 && (strcmp(argv[2], "add") == 0 || strcmp(argv[2], "sub") == 0 || strcmp(argv[2], "mul") == 0 || strcmp(argv[2], "div") == 0)) exit(1);

    if (strcmp(argv[2], "add") != 0 && strcmp(argv[2], "sub") != 0 && strcmp(argv[2], "mul") != 0 && strcmp(argv[2], "div") != 0) {
        if (strcmp(argv[2], "arr") == 0) take_arr(argv);
        else take_data(argv[1], argv[2]);
    }
    else {
        take_expression(argv[1], argv[2], argv[3], argv[4]);
    }
}