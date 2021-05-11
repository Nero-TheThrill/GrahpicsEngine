#pragma once
#include<glm/glm.hpp>
class Light
{
public:
    glm::vec3 GetLightPosition();
    void SetLightPosition(glm::vec3 input_position);

    glm::vec4 GetLightColor();
    void SetLightColor(glm::vec4 input_color);
private:
    glm::vec3 position = glm::vec3{0.0f};
    glm::vec4 color = glm::vec4{ 1.0f };
};

