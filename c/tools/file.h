#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

int fcontent(FILE *f, char **content);

#ifdef UTILS_IMPLEMENTATION

int fcontent(FILE *f, char **content) {
    if (!f) { return 0; }
    
    fseek(f, 0, SEEK_END);
    size_t fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    *content = (char * )calloc(fsize + 1, sizeof(char));
    
    if (!(*content)) { 
        return 0;
    }

    fread(*content, sizeof(char), fsize, f);

    return 1;
}

#endif 

#endif 