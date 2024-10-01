#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string.h>
#include "../../tools/file.h"

typedef struct {
    GLuint id; 
    GLenum type;
    const char *filepath;
    char *content;
    size_t content_size;
} Shader;


Shader shader_init(const char *filepath, GLenum type);
void shader_create(Shader *shader);
void shader_load_source(Shader *shader);
void shader_compile(Shader *shader);
void shader_delete(Shader *shader);
void shader_clean(Shader *shader);

#endif