#include "Light.h"

glm::vec3 Light::GetLightPosition()
{
    return position;
}

void Light::SetLightPosition(glm::vec3 input_position)
{
    position = input_position;
}

glm::vec4 Light::GetLightColor()
{
    return color;
}

void Light::SetLightColor(glm::vec4 input_color)
{
    color = input_color;
}
