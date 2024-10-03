#ifndef MODEL_H
#define MODEL_H

#include <VBO/vbo.hpp>
#include <VAO/vao.hpp>
#include <EBO/ebo.hpp>
#include <SHADER/shader.hpp>
#include <PROGRAM/program.hpp>
#include <vector>

typedef struct {
    GLuint attributeComponentsCount;
    GLenum attributeType;
    GLboolean normalizeIt; 
    size_t offsetOfAttribute;
} VertexAttribute;

class Model {
    private:
        GLfloat *vs = NULL;
        size_t vcount = 0;
        size_t vsize = 0;
        GLenum vusage = GL_NONE;

        VBO *vbo = NULL;
        VAO *vao = NULL;

        char *vshaderFilePath = NULL;
        char *fshaderFilePath = NULL;

        Shader *vshader = NULL;
        Shader *fshader = NULL;
        Program *prog   = NULL;

        size_t attributeIndex = 0;

        std::vector<VertexAttribute> vattrs;
    
        size_t useIndex();
        size_t getVertexSize();

    public:
        Model(GLfloat *vs, size_t vcount, size_t vsize, GLenum vusage);
        void update(GLfloat *vs, size_t vcount, size_t vsize);
        void SetShaderFilePath(unsigned long int whichShader, char *shaderFilePath);
        void schema(GLuint attributeComponentsCount, GLenum attributeType, GLboolean normalizeIt, size_t offsetOfAttribute);
        void cleanSchema();
        void setup();
        void model();
        void prerender();
        void render();
        ~Model();
};


#endif