#pragma once
#include <glm/glm.hpp>
class Camera
{
public:
    void View(glm::vec3 v);
    void Projection(float degree, float near, float far);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    void Move(glm::vec3 v);
    void MouseMoveUpdate();
    void MouseScrollUpdate();

private:
    glm::mat4 view = glm::mat4(1.0f), projection = glm::mat4(1.0f);
    glm::vec3 cam_position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cam_target = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    float fov = 45.f;
    bool firstMouse = true;
    float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch = 0.0f;
    float lastX = 800.0f / 2.0;
    float lastY = 600.0 / 2.0;
    float near, far;
};

