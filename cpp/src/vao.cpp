#include <VAO/vao.hpp>

VAO::VAO(VBO *vbo) {
    this->vbo = vbo;
}

// create the VAO object in the OpenGL context
void VAO::create() {
    glCreateVertexArrays(1, &this->id);
}

// update the VAO object with another VBO object  
void VAO::update(VBO *vbo) {
    this->vbo = vbo;
}

// set and design the layout on the VBO object attached to the current object
void VAO::design(GLuint index, GLuint attribComponentsCount, GLenum attribType, GLboolean isNormalizeNeeded, GLsizei vertexTotalSize, size_t offset) {
    this->bind();
    this->vbo->bind();
    
    glVertexAttribPointer(index, attribComponentsCount, attribType, isNormalizeNeeded, vertexTotalSize, (const void * ) offset);
    glEnableVertexAttribArray(index);

    this->vbo->unbind();
    this->unbind();
}

void VAO::bind() {
    glBindVertexArray(this->id);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::remove() {
    glDeleteVertexArrays(1, &this->id);
}