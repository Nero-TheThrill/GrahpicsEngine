#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Component.h"

class Mesh : public Component
{
public:
    Mesh();
    void Init();
    void Bind();
    void Draw();
    void UnBind();
    ~Mesh();
private:
    GLuint VAO;
    GLuint VBO;
   // GLuint EBO;
    int index_size;
    std::vector<glm::vec3> position;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec2> uv;
};

