#pragma once
#include <string>
#include <vector>
#include<glm/glm.hpp>

#include "Material.h"

class Object
{
public:
    Object();
    void SetObject(const std::string& filepath, const std::string& shader_id);
    ~Object();
    void LoadObject(const std::string& path);
    void Update();

    void draw();
    void pick_shader(const std::string& name);
    bool alive = true;
    unsigned id;
private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    int index_size;
    std::vector<glm::vec3> position;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec4> color;
    Material material;


    unsigned int texture1;
    int width, height, nrChannels;
    unsigned char* data;

    //translate rotate scale... components needed
};
