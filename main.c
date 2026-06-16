#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "take_data.h"


int main(int argc, char **argv){
    if (argc < 2) exit(1);
    take_data(argv[1], argv[2]);
}