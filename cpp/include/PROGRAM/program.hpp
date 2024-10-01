#ifndef PROGRAM_HPP_
#define PROGRAM_HPP_

#include <iostream>
#include <glad/glad.h>

class Program {
    private:
        GLuint id;

    public:
        Program() {};
        void create();
        void attachShader(GLuint shaderID);
        int link();
        GLint findVariable(const char *id);
        void use();
        void remove();
};


#endif