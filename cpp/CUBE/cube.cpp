#include <SDL2/SDL.h>
#include <VAO/vao.hpp>
#include <VBO/vbo.hpp>
#include <EBO/ebo.hpp>
#include <SHADER/shader.hpp>
#include <PROGRAM/program.hpp>
#include "CAMERA/camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


GLfloat vs[] = {
    // Position             // Color (RGB)
    // Front face
    -1.0f, -1.0f,  1.0f,   0.0f, 1.0f, 0.0f,   // Bottom-left  (Red)
     1.0f, -1.0f,  1.0f,   0.0f, 1.0f, 0.0f,   // Bottom-right (Green)
     1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 0.0f,   // Top-right    (Blue)
    -1.0f,  1.0f,  1.0f,   0.0f, 1.0f, 0.0f,   // Top-left     (Yellow)

    // Back face
    -1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 0.0f,   // Bottom-left  (Purple)
     1.0f, -1.0f, -1.0f,   0.0f, 1.0f, 0.0f,   // Bottom-right (Cyan)
     1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f,   // Top-right    (Orange)
    -1.0f,  1.0f, -1.0f,   0.0f, 1.0f, 0.0f    // Top-left     (Gray)
};


GLuint indices[] = {
    // Front face (CCW)
    0, 1, 2,   // First triangle
    0, 2, 3,   // Second triangle

    // Back face (CCW)
    4, 5, 6,   // First triangle
    4, 6, 7,   // Second triangle

    // Left face (CCW)
    4, 0, 3,   // First triangle
    4, 3, 7,   // Second triangle

    // Right face (CCW)
    1, 5, 6,   // First triangle
    1, 6, 2,   // Second triangle

    // Top face (CCW)
    3, 2, 6,   // First triangle
    3, 6, 7,   // Second triangle

    // Bottom face (CCW)
    4, 0, 1,   // First triangle
    4, 1, 5    // Second triangle
};



size_t vertexComponents = 6;
size_t vertexSize = vertexComponents * sizeof(GLfloat);


SDL_Window *window = NULL;
SDL_GLContext glContext =  NULL;

int windowHeight =    600;
int windowWidth  =    480;
const char *windowTitle  =  "Cube using SDL and OpenGL with  GLAD";

bool quit = false;

VBO vbo(vs, sizeof(vs), GL_STATIC_DRAW);
VAO vao(&vbo);
EBO ebo(indices, sizeof(indices)/sizeof(GLuint), GL_STATIC_DRAW);

char *vshaderFilePath = "./cube.vshader.glsl";
char *fshaderFilePath = "./cube.fshader.glsl";

Shader vshader(vshaderFilePath, GL_VERTEX_SHADER);
Shader fshader(fshaderFilePath, GL_FRAGMENT_SHADER);

Program prog;

Camera camera;

void init() {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "could not initialze the SDL library" << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "could not initialize the window" << std::endl;
        SDL_Quit();
        exit(EXIT_FAILURE);        
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "could not initialize the OpenGL context" << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        std::cerr << "could not load the OpenGL functions" << std::endl;
        SDL_DestroyWindow(window);
        SDL_GL_DeleteContext(glContext);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);
}

void clean();

void setup() {
    GLenum err = GL_NONE;

    vbo.create();
    vbo.setBuffer();


    vao.create();
    vao.design(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
    vao.design(1, 3, GL_FLOAT, GL_FALSE, vertexSize, 3 * sizeof(GLfloat));

    ebo.create();
    ebo.setBuffer();

    vshader.create();
    if (!vshader.loadSource()) { goto error; }
    if (!vshader.compile()) { goto error; }

    fshader.create();
    if (!fshader.loadSource()) { goto error; }
    if (!fshader.compile()) { goto error; }
    
    prog.create();
    prog.attachShader(vshader.getId());
    prog.attachShader(fshader.getId());
    if (!prog.link()) { goto error; };
    
    vshader.remove();
    fshader.remove();

    return;

error:
    clean();
    exit(EXIT_FAILURE);
}

void prerender() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, windowWidth, windowHeight);
    
    
    vao.bind();
    ebo.bind();
    prog.use();
}

void render() {
    GLenum error;
    glDrawElements(GL_TRIANGLES, ebo.getIndicesCount(), GL_UNSIGNED_INT, 0);

    error = glGetError();
    if (error) {
        std::cerr << "error: " << error << std::endl;
    } 

    SDL_GL_SwapWindow(window);
}


void clean() {
    vbo.remove();
    vao.remove();
    ebo.remove();
    prog.remove();
}

float rotate = 0.0f;

void update() {
    rotate += glm::pi<float>() / 10;

    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) { 
            quit = 1;
            return;
        }

        if (e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = 1;
                    break;
                case SDLK_z:
                    camera.moveForward();
                    break;
                case SDLK_s:
                    camera.moveBackward();
                    break;
                case SDLK_d:
                    camera.moveRight();
                    break;
                case SDLK_q:
                    camera.moveLeft();
                    break;
            }
        }
    }


    glm::mat4 model      = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 view       = glm::mat4(1.0f);

    model                = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
    model                = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f));


    view                 = camera.getMatrix();
    projection           = glm::perspective(glm::radians(45.0f), (float) windowWidth / (float) windowHeight, 0.1f, 100.0f);


    GLuint modelLocation = prog.findVariable("Model");
    if (modelLocation < 0) {
        std::cerr << "could not find the model matrix location" << std::endl;        
    } else {
        prog.use();
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
    }


    GLuint viewLocation = prog.findVariable("View");
    if (viewLocation < 0) {
        std::cerr << "could not find the view matrix location" << std::endl;        
    } else {
        prog.use();
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    }

    GLuint projectionLocation = prog.findVariable("Projection");
    if (projectionLocation < 0) {
        std::cerr << "could not find the projection matrix location" << std::endl;
    } else {
        prog.use();
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
    }
}

int main(void) {
    init();
    setup();

    while(!quit) {
        update();
        prerender();
        render();
    }

    clean();
    return 0;
}
