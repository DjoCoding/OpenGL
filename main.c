#include <stdbool.h>

#define UTILS_IMPLEMENTATION

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include <VBO/vbo.h>
#include <VAO/vao.h>
#include <SHADER/shader.h>
#include <PROGRAM/program.h>

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_GLContext context = {0};

const int window_width = 680;
const int window_height = 420;
const char *title = "SDL";


VBO vbo = {0};
VAO vao = {0};


const char *vshader_filepath = "./Shaders/vshader.glsl";
const char *fshader_filepath = "./Shaders/fshader.glsl";

Shader vshader = {0};
Shader fshader = {0};

Program prog = {0};

GLfloat vertices[] = {
    // x,    y,     z
    0.5,   -0.5,    0,
    -0.5,  -0.5,    0,
    0,      0.5,    0,
};

bool quit = false;

void clean(void);

void init(void) { 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "failed to initialize the SDL library\n");
        exit(EXIT_FAILURE);
    };


    window = SDL_CreateWindow(title, 0, 0, window_width, window_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "failed to initialize the SDL window\n");
        SDL_Quit();
        exit(EXIT_FAILURE);
    }  
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    context = SDL_GL_CreateContext(window);

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        fprintf(stderr, "could not import the OpenGL functions\n");
        clean();
        exit(EXIT_FAILURE);
    }
}

void setup(void) {
    vbo = vbo_init(vertices, 9 *  sizeof(GLfloat), GL_STATIC_DRAW);
    vbo_create(&vbo);
    vbo_setData(&vbo);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "OpenGL Error: %d\n", error);
    }

    vao_create(&vao);
    vao_bind(&vao);
    vao_set_layout_and_enable(&vao, &vbo, 0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, 0);

    vshader = shader_init(vshader_filepath, GL_VERTEX_SHADER);
    shader_create(&vshader);
    shader_load_source(&vshader);
    shader_compile(&vshader);
    
    fshader = shader_init(fshader_filepath, GL_FRAGMENT_SHADER);
    shader_create(&fshader);
    shader_load_source(&fshader);
    shader_compile(&fshader);
    
    program_create(&prog);
    program_attach_shader(&prog, &vshader);
    program_attach_shader(&prog, &fshader);
    program_link(&prog);

    shader_delete(&vshader);
    shader_delete(&fshader);
}

void getInfo(void) {
    const char *gl_version = glGetString(GL_VERSION);
    fprintf(stdout, "OpenGL version: %s\n", gl_version);
}


void update(void) {
    SDL_Event e =  {0};
    while(SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) { 
            quit = true;
            return;
        }
    }   
}


void pre_render(void) {
    glClearColor(0.24, 0.24, 0.24, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void render(void) {
    vao_bind(&vao);
    vbo_bind(&vbo);
    program_use(&prog);

    glViewport(0, 0, window_width, window_height);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    SDL_GL_SwapWindow(window);
}   


void clean(void) {
    shader_clean(&vshader);
    shader_clean(&fshader);

    vao_clean(&vao);
    vbo_clean(&vbo);

    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);
    SDL_Quit();
}

int main(void) {
    init();
    setup();

    while(!quit) {
        update();
        pre_render();
        render();
    }

    clean();
    return 0;
}