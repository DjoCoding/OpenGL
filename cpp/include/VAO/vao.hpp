#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include <VBO/vbo.hpp>

class VAO {
    private: 
        GLuint id       = 0;
        VBO *vbo        = nullptr;

    public:
        VAO(VBO *vbo);
        void create();
        void update(VBO *vbo);
        void design(GLuint index, GLuint attribComponentsCount, GLenum attribType, GLboolean isNormalizeNeeded, GLsizei vertexTotalSize, size_t offset);
        void bind();
        void unbind();
        void remove();
};


#endif