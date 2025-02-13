#include <PROGRAM/program.h>

void program_create(Program *prog) {
    prog->id = glCreateProgram();
}

void program_attach_shader(Program *prog, Shader *shader) {
    glAttachShader(prog->id, shader->id);
}

int program_link(Program *prog) {
    glLinkProgram(prog->id);

    int success; 
    glGetProgramiv(prog->id, GL_LINK_STATUS, &success);
    
    if (!success) {
        char infoLog[512] = {0};
        glGetProgramInfoLog(prog->id, 512, NULL, infoLog);
        fprintf(stderr, "Program Linking Failed: %s\n", infoLog);
    }

    return success;
}

void program_use(Program *prog) {
    glUseProgram(prog->id);
} 

GLint prog_find_uniform(Program *prog, char *uniform_id) {
    return glGetUniformLocation(prog->id, uniform_id);
}

void program_delete(Program *prog) {
    glDeleteProgram(prog->id);
}
