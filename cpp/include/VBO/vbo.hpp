#ifndef VBO_H
#define VBO_H

#include <iostream>
#include <glad/glad.h>

class VBO {
    private: 
        GLuint id       = 0;
        GLfloat *vs     = nullptr;
        size_t vsize    = 0;
        GLenum vusage   = GL_NONE;
        

    public:
        VBO(GLfloat *vs, size_t vsize, GLenum vusage);
        void create();
        void update(GLfloat *vs, size_t vsize, GLenum vusage);
        void setBuffer();
        void bind();
        void unbind();
        void remove();
};


#endif