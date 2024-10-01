#include <SDL2/SDL.h>
#include <VAO/vao.hpp>
#include <VBO/vbo.hpp>
#include <SHADER/shader.hpp>
#include <PROGRAM/program.hpp>

GLfloat vs[] = {
    // x,       y,      z,      r,      g,      b 
    -0.5,    -0.5,    0.0f,   1.0f,   0.0f,   0.0f,
    +0.5,    -0.5,   -0.0f,   0.0f,   1.0f,   0.0f,
    +0.0,    +0.5,    0.0f,   0.0f,   0.0f,   1.0f, 
};

size_t vertexComponents = 6;
size_t vertexSize = vertexComponents * sizeof(GLfloat);

SDL_Window *window = NULL;
SDL_GLContext glContext =  NULL;

int windowHeight =    600;
int windowWidth  =    480;
const char *windowTitle  =  "SDL and OpenGL with  GLAD";

bool quit = false;

VBO vbo(vs, sizeof(vs), GL_STATIC_DRAW);
VAO vao(&vbo);

char *vshaderFilePath = "./shaders/vshader.glsl";
char *fshaderFilePath = "./shaders/fshader.glsl";

Shader vshader(vshaderFilePath, GL_VERTEX_SHADER);
Shader fshader(fshaderFilePath, GL_FRAGMENT_SHADER);

Program prog;

float uOffset = 0;
float speed = 2;

void clean();

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

    return;
}


void setup() {
    GLenum err = GL_NONE;

    vbo.create();
    vbo.setBuffer();


    vao.create();
    vao.design(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
    vao.design(1, 3, GL_FLOAT, GL_FALSE, vertexSize, 3 * sizeof(GLfloat));

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

void update() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) { 
            quit = 1;
            return;
        }

        if (e.type == SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
                case SDLK_UP: 
                    uOffset += 0.01f;
                    break;
                case SDLK_DOWN:
                    uOffset -= 0.01f;
                    break;
                case SDLK_ESCAPE:
                    quit = 1;
                    break;
            }
        }
    }

    char *uniformId = "uOffset";

    GLint location = prog.findVariable(uniformId);
    if (location >= 0) {
        prog.use();
        glUniform1f(location, speed * uOffset);
    } else {
        std::cerr << "failed to find the uniform variable `" << glUniform1f << "`" << std::endl;
    }
}

void render() {
    GLenum err;

    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    vao.bind();
    vbo.bind();
    prog.use();

    err = glGetError();
    if (err) {
        std::cerr << "error: " << err << std::endl;
    }

    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(window);
}

void clean() {
    if (window) { 
        SDL_DestroyWindow(window);
    }
    
    if (glContext) {
        SDL_GL_DeleteContext(glContext);        
    }

    SDL_Quit();
}


int main(void) {
    init();

    setup();

    while(!quit) {
        update();
        render();
    }

    clean();

    return 0;
}