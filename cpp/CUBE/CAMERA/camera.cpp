#include "./camera.hpp"


Camera::Camera() {
    this->eye    = glm::vec3(0);
    this->target = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up     = glm::vec3(0.0f, 1.0f, 0.0f);
    this->speed  = 1.0f;
    this->angle  = glm::radians(10.0f);
}

void Camera::moveForward() {
    this->eye += speed * this->target;
}

void Camera::moveBackward() {
    this->eye -= speed * this->target;
}

void Camera::moveLeft() {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), this->angle, glm::vec3(0.0f, 1.0f, 0.0f));
    this->target = glm::vec3(rotation * glm::vec4(this->target, 1.0f));
}


void Camera::moveRight() {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), -this->angle, glm::vec3(0.0f, 1.0f, 0.0f));
    this->target = glm::vec3(rotation * glm::vec4(this->target, 1.0f));
}

glm::mat4 Camera::getMatrix() {
    return glm::lookAt(this->eye, this->eye + this->target, this->up);
}