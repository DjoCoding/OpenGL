#include <APP/app.h>

App app_create(int window_width, int window_height, char *window_title) {
    App this = {0};
    this.window_width = window_width;
    this.window_height = window_height;
    this.window_title = window_title;
    return this;
}

void app_init(App *this) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "failed to initialize the SDL library\n");
        exit(EXIT_FAILURE);
    };


    this->window = SDL_CreateWindow(this->window_title, 0, 0, this->window_width, this->window_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if (!this->window) {
        fprintf(stderr, "failed to initialize the SDL window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }  
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    this->glContext = SDL_GL_CreateContext(this->window);

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        fprintf(stderr, "could not import the OpenGL functions\n");
        app_clean(this);
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);

    this->state = RUNNING;
}


void app_set_state(App *this, App_State state) {
    this->state = state;
}

int app_is_running(App *this) {
    return (this->state == RUNNING);
}

void app_quit(App *this) {
    this->state = NOT_RUNNING;
}

void app_set_bg(App *this, V4 bg) {
    this->bg = bg;
}

void app_clear(App *this) {
    glClearColor(this->bg.x, this->bg.y, this->bg.z, this->bg.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void app_pre_render(App *this) {
    glViewport(0, 0, this->window_width, this->window_height);
    app_clear(this);
}

void app_swap_buffers(App *this) {
    SDL_GL_SwapWindow(this->window);
}

void app_clean(App *this) {
    if (this->window) { SDL_DestroyWindow(this->window); }
    if (this->glContext) { SDL_GL_DeleteContext(this->glContext); }
    SDL_Quit();
}