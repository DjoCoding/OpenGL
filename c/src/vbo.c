#include <VBO/vbo.h>

VBO vbo_init(float *vs, size_t vsize, GLenum vusage) {
    VBO vbo = {0};
    vbo.vs = vs;
    vbo.vsize = vsize;
    vbo.vusage = vusage;
    return vbo;
}

void vbo_create(VBO *vbo) {
    glGenBuffers(1, &vbo->id);
}

void vbo_setData(VBO *vbo) {
    vbo_bind(vbo);
    glBufferData(GL_ARRAY_BUFFER, vbo->vsize, (const void *)vbo->vs, vbo->vusage);
}

void vbo_update(VBO *vbo, float *vs, size_t vsize, GLenum vusage) {
    vbo->vs = vs;
    vbo->vsize = vsize;
    vbo->vusage = vusage;
}

void vbo_bind(VBO *vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
}

void vbo_unbind(VBO *vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vbo_clean(VBO *vbo) {
    glDeleteBuffers(1, &vbo->id);
}

