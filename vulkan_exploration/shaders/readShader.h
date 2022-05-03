#include <stdint.h>

struct shaderData {
    char *binary;
    uint32_t num;
};

typedef struct shaderData shaderData;

shaderData *readShader(const char *path);

void freeShaderData(shaderData *data);
