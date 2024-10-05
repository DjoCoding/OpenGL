#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {
    private:
        glm::vec3 target;
        glm::vec3 up;
        glm::vec3 eye;
        float speed;
        float angle;

    public:
        Camera();
        void moveForward();
        void moveBackward();
        void moveLeft();
        void moveRight();
        glm::mat4 getMatrix();
};


#endif