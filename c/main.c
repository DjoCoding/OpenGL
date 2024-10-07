#define UTILS_IMPLEMENTATION
#define VEC4_IMPLEMENTATION

#define VEC3_IMPLEMENTATION
#include <MATH/vec/vec3.h>

#define MAT4_IMPLEMENTATION
#include <MATH/mat/mat4.h>

#define VEC4_IMPLEMENTATION
#include <MATH/vec/vec4.h>

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



#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#define VERTEX_SHADER_FILE_PATH     "./Shaders/vshader.glsl"
#define FRAGMENT_SHADER_FILE_PATH   "./Shaders/fshader.glsl"


#define ANGLE_SPEED 10.0f

float angle = 0.0f;

void mesh_update(Mesh *this, float dt) {
    SDL_Event e =  {0};
    angle += ANGLE_SPEED * dt;
    
    while(SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) { 
            app_quit(&app);
            return;
        }

        switch(e.key.keysym.sym) {
            case SDLK_ESCAPE:
                app_quit(&app);
                return;
        }
    }   

    Mat4x4 model = mat4_init(1.0f);
    model        = mat4_rotate(model, angle, v3(0.0f, 0.0f, 1.0f));

    GLint model_location = prog_find_uniform(&this->prog, "MODEL");
    if (model_location < 0) {
        fprintf(stderr, "could not find the MODEL uniform variable\n");
    } else {
        program_use(&this->prog);
        glUniformMatrix4fv(model_location, 1, GL_FALSE, model.cs);
    }
}

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

    uint32_t prev =  SDL_GetTicks();
    while(app_is_running(&app)) {
        uint32_t now = SDL_GetTicks();
        float dt = (float) (now - prev) / (1e3);

        mesh_update(&triangle, dt);

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