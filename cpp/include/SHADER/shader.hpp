#ifndef SHADER_H
#define SHADER_H


#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>

class Shader {
    private:
        GLuint id                   = 0;
        char *filepath              = nullptr;
        char *fileContent           = nullptr;
        size_t fileLength           = 0;
        GLenum type                 = GL_NONE;
        const char *strType();

    public:
        Shader(char *filepath, GLenum type);
        void create();
        bool loadSource();
        bool compile();
        GLuint getId();
        void remove();
        void clean();
};


#endif