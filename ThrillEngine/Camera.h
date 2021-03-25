#pragma once
#include <glm/glm.hpp>
class Camera
{
public:
    void View(glm::vec3 v);
    void Projection(float radian, float near, float far);
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
private:
    glm::mat4 view = glm::mat4(1.0f), projection = glm::mat4(1.0f);
};

