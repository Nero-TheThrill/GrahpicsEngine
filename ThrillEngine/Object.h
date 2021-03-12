#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include<glm/glm.hpp>

class Object
{
public:
    void LoadObject(const std::string& path);
    ~Object();
    virtual void draw();
private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    int index_size;
    std::vector<glm::vec3> position;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec4> color;
};
