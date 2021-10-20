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
    glm::vec3 direction=glm::vec3{1,0,0}; //Directional
    glm::vec3 ambient = glm::vec3{ 0.7f,0.7f,1.0f }, diffuse = glm::vec3{ 1,1,1 }, specular = glm::vec3{ 1,1,1 };//All
    float inner_angle=0.2f, outer_angle=0.5f, falloff=1;
};

