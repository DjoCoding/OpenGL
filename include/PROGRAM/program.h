#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <SHADER/shader.h>

typedef struct {
    GLuint id;
} Program;

void program_create(Program *prog);
void program_attach_shader(Program *prog, Shader *shader);
void program_link(Program *prog);
void program_use(Program *prog);

#endif