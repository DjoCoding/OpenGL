#ifndef EBO_HPP
#define EBO_HPP

#include <iostream>
#include <glad/glad.h>

class EBO {
    private:
        GLuint id       = 0;
        GLuint *indices = nullptr;
        size_t count    = 0;
        GLenum iusage   = 0;

    public:
        EBO(GLuint *indices, size_t count, GLenum iusage);
        void create();
        void update(GLuint *indices, size_t count, GLenum iusage);
        void setBuffer();
        void bind();
        void unbind();
        GLuint *getIndices();
        size_t getIndicesCount();
        GLuint getId();
        void remove();
};


#endif