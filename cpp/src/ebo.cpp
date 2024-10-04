#include <EBO/ebo.hpp>

EBO::EBO(GLuint *indices, size_t count, GLenum iusage) {
    this->indices = indices;
    this->count = count;
    this->iusage = iusage;
}

void EBO::create() {
    glGenBuffers(1, &this->id);
}

void EBO::setBuffer() {
    this->bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->count *  sizeof(GLuint), this->indices, this->iusage);
    this->unbind();    
}


void EBO::bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->id);
}

void EBO::unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::update(GLuint *indices, size_t count, GLenum iusage) {
    this->indices = indices;
    this->count = count;
    this->iusage = iusage;
}

GLuint *EBO::getIndices() {
    return this->indices;
}

size_t EBO::getIndicesCount() {
    return this->count;
}

GLuint EBO::getId() {
    return this->id;
}

void EBO::remove() {
    glDeleteBuffers(1, &this->id);
}

