#include <SHADER/shader.hpp>

Shader::Shader(char *filepath, GLenum type) {
    this->filepath = filepath;
    this->type = type;
}

// create a shader in the OpenGL context of the type specified in the current object
void Shader::create() {
    this->id = glCreateShader(this->type);    
}

// load the source code of the shader from a file and load it to the OpenGL context
bool Shader::loadSource() {
    std::ifstream shaderFile(this->filepath);

    if (!shaderFile.is_open()) {
        std::cerr << "could not open the " << this->strType() << " shader file" << std::endl;
        return false;
    }

    std::stringstream content;
    content << shaderFile.rdbuf();

    std::string contentString = content.str();

    this->fileContent = (char *) contentString.c_str();
    this->fileLength  =  contentString.length();

    glShaderSource(this->id, 1, (const GLchar *const *) &this->fileContent, (const GLint *) &this->fileLength);

    return true;
}

// compile the shader and return an error flag if compilation failed
bool Shader::compile() {
    glCompileShader(this->id);

    bool success = true;
    glGetShaderiv(this->id, GL_COMPILE_STATUS, (GLint *) &success);

    if (!success) {
        GLchar error[1024] = {0};
        GLsizei length = 0;    

        glGetShaderInfoLog(this->id, 1024, &length, (GLchar *) &error);

        std::cerr << "Compilation Error in the " << this->strType() << " shader: " << error << std::endl;
    }

    return success;
} 

// return the shader type in a form of a string
const char *Shader::strType() {
    if(this->type == GL_VERTEX_SHADER) { return "vertex"; }
    if(this->type == GL_FRAGMENT_SHADER) { return "fragment"; }
    return NULL;
}

// return the current Shader Object id
GLuint Shader::getId() {
    return this->id;
}

// remove the Shader object from the OpenGL context
void Shader::remove() {
    glDeleteShader(this->id);
}

// clean the data allocated by the shader
void Shader::clean() {
    if (this->fileContent) free(this->fileContent);
}

