#include <MODEL/model.hpp>

// Model(GLfloat *vs, size_t vcount, size_t vsize);
// void create();
// void update(GLfloat *vs, size_t vcount, size_t vsize);
// void render();
// void clean();

Model::Model(GLfloat *vs, size_t vcount, size_t vsize, GLenum vusage) {
    this->vs = vs;
    this->vcount = vcount;
    this->vsize = vsize;
    this->vusage = vusage;
}

void Model::update(GLfloat *vs, size_t vcount, size_t vsize) {
    this->vs = vs;
    this->vcount = vcount;
    this->vsize = vsize;
}

size_t Model::useIndex() {
    return this->attributeIndex++;
}

size_t Model::getVertexSize() {
    return this->vsize / this->vcount;
}

void Model::schema(GLuint attributeComponentsCount, GLenum attributeType, GLboolean normalizeIt, size_t offsetOfAttribute) {
    this->vattrs.push_back((VertexAttribute) { attributeComponentsCount, attributeType, normalizeIt, offsetOfAttribute });
}

void Model::cleanSchema() {
    this->attributeIndex = 0;
    this->vattrs.clear();
}

void Model::model() {
    for(size_t i = 0; i < this->vattrs.size(); ++i) {
        VertexAttribute va = this->vattrs.at(i);
        this->vao->design(this->useIndex(), va.attributeComponentsCount, va.attributeType, va.normalizeIt, this->getVertexSize(), va.offsetOfAttribute);
    }
}

void Model::SetShaderFilePath(unsigned long int whichShader, char *shaderFilePath) {
    if (whichShader == GL_VERTEX_SHADER) {
        this->vshaderFilePath = shaderFilePath;
        return;
    }

    if (whichShader == GL_FRAGMENT_SHADER) {
        this->fshaderFilePath = shaderFilePath;
        return;
    }

    std::cerr << "ERROR: no shader found with the code " << whichShader << std::endl;
    // exit(EXIT_FAILURE);
}

void Model::setup() {
    // initialize the VBO object
    this->vbo = new VBO(this->vs, this->vsize, this->vusage);
    this->vbo->create();
    this->vbo->setBuffer();

    // initialize the VAO object
    this->vao = new VAO(this->vbo);
    this->vao->create();
    // let the modeling to the Model::model method which will set the models attributes before the drawing starts

    this->vshader = new Shader(this->vshaderFilePath, GL_VERTEX_SHADER);
    this->vshader->create();

    if (!this->vshader->loadSource()) { 
        std::cerr << "could not load the source file for the vertex shader" << std::endl;
    };

    if (!this->vshader->compile()) {
        std::cerr << "failed to compile the vertex shader" << std::endl;
    }

    this->fshader = new Shader(this->fshaderFilePath, GL_FRAGMENT_SHADER); 
    this->fshader->create();


    if (!this->fshader->loadSource()) { 
        std::cerr << "could not load the source file for the fragment shader" << std::endl;
    };

    if (!this->fshader->compile()) {
        std::cerr << "failed to compile the fragment shader" << std::endl;
    }

    this->prog = new Program();
    this->prog->create();
    this->prog->attachShader(this->vshader->getId());
    this->prog->attachShader(this->fshader->getId());
    
    if (!this->prog->link()) {
        std::cerr << "failed to link the shader program" << std::endl;
    }

    this->vshader->remove();
    this->fshader->remove();
}

void Model::prerender() {
    this->vao->bind();
    this->vbo->bind();
    this->prog->use();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Model::render() {
    glDrawArrays(GL_TRIANGLES, 0, this->vcount);
}

Model::~Model() {
    this->vbo->remove();
    this->vao->remove();

    delete this->vbo;
    delete this->vao;

    delete this->vshader;
    this->vshader->clean();

    this->fshader->clean();
    delete this->fshader;

    this->prog->remove();
    delete this->prog;
}
