#include <VBO/vbo.hpp>

VBO::VBO(GLfloat *vs, size_t vsize, GLenum vusage) {
    this->vs = vs;
    this->vsize = vsize;
    this->vusage = vusage;
}

// initialize the VBO object in the OpenGL context
void VBO::create() {
    glGenBuffers(1, &this->id);
}

// set the current VBO object buffer data in the OpenGL context
void VBO::setBuffer() {
    this->bind();
    glBufferData(GL_ARRAY_BUFFER, this->vsize, this->vs, this->vusage);
    this->unbind();
}

// set the current VBO object attributes
void VBO::update(GLfloat *vs, size_t vsize, GLenum vusage) {
    this->vs = vs;
    this->vsize = vsize;
    this->vusage = vusage;
}

// select the buffer array using the VBO object's id
void VBO::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->id);
} 

void VBO::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::remove() {
    glDeleteBuffers(1, &this->id);
}