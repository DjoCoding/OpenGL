#include <SHADER/shader.h>


Shader shader_init(const char *filepath, GLenum type) {
    Shader shader = {0};
    shader.type = type;
    shader.filepath = filepath;
    return shader;
}

void shader_create(Shader *shader) {
    shader->id = glCreateShader(shader->type);
}

void shader_load_source(Shader *shader) {
    const char *shader_type_cstr = (shader->type == GL_VERTEX_SHADER) ? "vertex" : "fragment";
    FILE *f = fopen(shader->filepath, "r");

    if (!f) { 
        fprintf(stderr, "could not open the %s shader source code file\n", shader_type_cstr);
        exit(EXIT_FAILURE);
    }

    if (!fcontent(f, &shader->content)) {
        fprintf(stderr, "could not read the %s shader file content\n", shader_type_cstr);
        exit(EXIT_FAILURE);
    }

    shader->content_size = strlen(shader->content);

    glShaderSource(shader->id, 1, (const GLchar *const *) &shader->content, (const GLint *) &shader->content_size);
}

void shader_compile(Shader *shader) {
    glCompileShader(shader->id);

    GLint success;
    glGetShaderiv(shader->id, GL_COMPILE_STATUS, &success);

    if (!success) {
        const char *shader_type_cstr = (shader->type == GL_VERTEX_SHADER) ? "vertex" : "fragment";

        char infoLog[512] = {0};
        size_t length = 0;
        
        glGetShaderInfoLog(shader->id, 512, (GLsizei *) &length, infoLog);
        printf("%s shader compilation failed: %s\n", shader_type_cstr, infoLog);
        
        exit(EXIT_FAILURE);
    }
}

void shader_delete(Shader *shader) {
    glDeleteShader(shader->id);
}

void shader_clean(Shader *shader) {
    free(shader->content);
}

