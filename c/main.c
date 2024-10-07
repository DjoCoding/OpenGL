#define UTILS_IMPLEMENTATION
#define VEC4_IMPLEMENTATION


#include <MESH/mesh.h>
#include <APP/app.h>


const char *vshader_filepath = "./Shaders/vshader.glsl";
const char *fshader_filepath = "./Shaders/fshader.glsl";


float vs[] = {
    // x,    y,     z,      r,      g,      b,
    0.5,   -0.5,    0,      1.0f,   0,      0, 
    -0.5,  -0.5,    0,      0,   1.0f,      0,
    0,      0.5,    0,      0,      0,   1.0f,
};
size_t stride  = 6 * sizeof(float);
size_t vscount = 3;


App app = {0};

Shader vshader = {0};
Shader fshader = {0};


#define GL_CLEAR_ERROR() while(glGetError() != GL_NO_ERROR) {} 

#define GL_GET_ERROR(func) \
    do { \
        GL_CLEAR_ERROR() \
        func; \
        GLenum error = glGetError(); \
        if (error != GL_NO_ERROR) {  \
            fprintf(stderr, "opengl-error: on line: %u, on function: %s, error code: %d\n", __LINE__, __FUNCTION__, error); \
            abort(); \
        } \
    } while(0)

// load the shader source code from a file and compile it 
Shader load_shader(const char *filepath, GLenum type) {
    Shader shader = shader_init(filepath, type);
    shader_create(&shader);

    if (!shader_load_source(&shader)) {
        exit(EXIT_FAILURE);
    }

    if (!shader_compile(&shader)) {
        exit(EXIT_FAILURE);
    }

    return shader;
}


void update(void) {
    SDL_Event e =  {0};
    while(SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) { 
            app_quit(&app);
            return;
        }

        switch(e.key.keysym.sym) {
            case SDLK_ESCAPE:
                app_quit(&app);
                break;
            default:
                break;
        }
    }   
}


#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#define VERTEX_SHADER_FILE_PATH     "./Shaders/vshader.glsl"
#define FRAGMENT_SHADER_FILE_PATH   "./Shaders/fshader.glsl"

int main(void) {
    // create the application together with the opengl context 
    app = app_create(WINDOW_WIDTH, WINDOW_HEIGHT, "triangle using opengl");
    app_init(&app);
    app_set_bg(&app, v4(0.0f, 0.0f, 0.0f, 1.0f));


    // load the used shaders 
    // always load the shaders after initializing the application (cannot be initialized without an opengl context)
    vshader = load_shader(VERTEX_SHADER_FILE_PATH, GL_VERTEX_SHADER);
    fshader = load_shader(FRAGMENT_SHADER_FILE_PATH, GL_FRAGMENT_SHADER);


    // create the mesh
    Mesh triangle = mesh_create(vs, vscount, stride * vscount, GL_STATIC_DRAW);

    // set the shaders used for this mesh, always set them before you initialize the mesh
    GL_GET_ERROR(mesh_set_shader(&triangle, vshader, GL_VERTEX_SHADER));
    GL_GET_ERROR(mesh_set_shader(&triangle, fshader, GL_FRAGMENT_SHADER));

    GL_GET_ERROR(mesh_init(&triangle));

    GL_GET_ERROR(mesh_design(&triangle, 0, 3, GL_FLOAT, GL_TRUE, 0));
    GL_GET_ERROR(mesh_design(&triangle, 1, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(float)));

    while(app_is_running(&app)) {
        update();
        app_pre_render(&app);
        GL_GET_ERROR(mesh_render(&triangle));
        app_swap_buffers(&app);
    }


    shader_delete(&vshader);
    shader_delete(&fshader);

    shader_clean(&vshader);
    shader_clean(&fshader);

    app_clean(&app);
    
    return 0;
}