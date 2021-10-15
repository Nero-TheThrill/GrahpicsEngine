#pragma once
#include "Object.h"

enum class LightType
{
    POINT,
    DIRECTIONAL,
    SPOT
};
class LightObject : public Object
{
public:
    LightObject(std::string n);
    LightType type = LightType::POINT;
    glm::vec3 direction=glm::vec3{0}; //Directional
    glm::vec3 ambient = glm::vec3{ 0.4f,0.4f,0.4f }, diffuse = glm::vec3{ 0.5f,0.5f,0.5f }, specular = glm::vec3{ 0.8f,0.8f,0.8f };//All
    float inner_angle=0, outer_angle=0, falloff=0;
};

