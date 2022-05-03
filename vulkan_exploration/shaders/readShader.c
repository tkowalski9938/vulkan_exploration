#include "readShader.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// frees shader data struct
void freeShaderData(shaderData *data) {
    free(data->binary);
    free(data);
}

// allocates memory in the heap, needs to be freed by client
shaderData *readShader(const char *path) {
    shaderData *data = malloc(sizeof(shaderData));
    
    FILE *ptr;
    
    assert(ptr = fopen(path, "rb"));

    fseek(ptr, 0L, SEEK_END);
    data->num = (uint32_t) ftell(ptr);
    rewind(ptr);
    
    data->binary = malloc(data->num * sizeof(char));
    
    assert(data->num == fread(data->binary, sizeof(char), data->num, ptr));
    
    fclose(ptr);
    ptr = NULL;
    
    return data;
}
