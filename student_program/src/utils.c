/*
 * utils.c copyright (c) Alexander Brown, March 2011
 */


#include <stdlib.h>
#include <stdio.h>

#include "utils.h"


void get_base_dir(char * base_dir) {
        FILE * file = fopen("config", "r");
        if(file == NULL) {
                printf("config file not found.");
                exit(1);
        }
        fscanf(file, "%s\n", base_dir);
        fclose(file);
}

