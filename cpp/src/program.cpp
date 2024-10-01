#include <PROGRAM/program.hpp>

void Program::create() {
    this->id = glCreateProgram();
}

void Program::attachShader(GLuint shaderID) {
    glAttachShader(this->id, shaderID);
}

int Program::link() {
    glLinkProgram(this->id);

    int success; 
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    
    if (!success) {
        char infoLog[512] = {0};
        glGetProgramInfoLog(this->id, 512, NULL, infoLog);
        std::cerr << "Program Linking Failed: " << infoLog << std::endl;
    }

    return success;
}

GLint Program::findVariable(const char *id) {
    return glGetUniformLocation(this->id, id);
}

void Program::use() {
    glUseProgram(this->id);
}

void Program::remove() {
    glDeleteProgram(this->id);
}
