#ifndef APP_H
#define APP_H

#include <MATH/vec/vec4.h>
#include <SDL2/SDL.h>
#include <glad/glad.h>

typedef enum {
    NOT_RUNNING = 0,
    PENDING,
    RUNNING,
} App_State;  

typedef struct {
    int window_width;                 // defines the width of the window
    int window_height;                // defines the height of the window 
    char *window_title;               // defines the window title
    SDL_Window *window;               // defines the SDL window
    SDL_GLContext glContext;          // defines th opengl context
    App_State state;                  // defines the application current state
    V4 bg;                            // defines the application window background color
} App;


// the app constructor
App app_create(int window_width, int window_height, char *window_title);

// initialize the app window and the opengl context
void app_init(App *this);

// set the background color of the app window
void app_set_bg(App *this, V4 bg);

// set the app state
void app_set_state(App *this, App_State state);

// return if the app is in the running state or no
int app_is_running(App *this);

// clear the app background color
void app_clear(App *this);

// set the window viewport and clear the background
void app_pre_render(App *this); 

// swap the app window buffers 
void app_swap_buffers(App *this);

// set the app state to the NOT_RUNNING state
void app_quit(App *this);

// clean the app ressources
void app_clean(App *this);

#endif