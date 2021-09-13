#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Transform : public Component
{
public:
    void Init();
    glm::mat4 GetTransformMatrix();
    ~Transform();
    void Translate(glm::vec3 input);
    void Rotate(float degree, glm::vec3 v);
    void RotateMove(float degree, glm::vec3 v);
    void Scale(glm::vec3 input);
    void Move(glm::vec3 input);
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 current_scale = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 current_rotate_axis = glm::vec3(1.0f);
    float current_rotate_degree = 0;
private:
    glm::mat4 transform = glm::mat4(1.0f), translate = glm::mat4(1.0f), rotate = glm::mat4(1.0f), scale = glm::mat4(1.0f);
};

