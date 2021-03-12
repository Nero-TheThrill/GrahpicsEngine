#pragma once
#include <vector>
#include "EngineCore.h"
#include "headers.h"
#include "Object.h"


class Graphics : public EngineCore
{
public:

    void Init() override;
    void Update() override;
    ~Graphics() override;
private:
    std::vector<glm::vec3> position;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normal;
    std::vector<std::vector<int>> face;
    glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f};
    Object obj;
};
extern Graphics* GRAPHICS;
