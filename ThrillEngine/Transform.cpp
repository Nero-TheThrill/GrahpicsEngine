#include "Transform.h"

#include "TimeManager.h"

void Transform::Init()
{
    transform = glm::mat4(1.0f);
}

glm::mat4 Transform::GetTransformMatrix()
{
    return translate * rotate * scale;
}


Transform::~Transform()
{
}

void Transform::Translate(glm::vec3 input)
{
    glm::mat4 tmp = glm::mat4(1.0f);
    translate = glm::translate(tmp, input);
    position = input;
}

void Transform::Rotate(float degree, glm::vec3 v)
{
    glm::mat4 tmp = glm::mat4(1.0f);
    rotate = glm::rotate(tmp, glm::radians(degree), v);
    current_rotate_degree = degree;
    current_rotate_axis = v;
}

void Transform::RotateMove(float degree, glm::vec3 v)
{
    glm::mat4 tmp = glm::mat4(1.0f);
    rotate *= glm::rotate(tmp, glm::radians(degree), v);
}

void Transform::Scale(glm::vec3 input)
{
    glm::mat4 tmp = glm::mat4(1.0f);
    scale = glm::scale(tmp, input);
    current_scale = input;
}

void Transform::Move(glm::vec3 input)
{
    translate = glm::translate(translate, input * TIMEMANAGER->deltaTime);
    position += input * TIMEMANAGER->deltaTime;
}

