#pragma once
#include <string>
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

class Object
{
public:
    Object();
    ~Object();
    void SetColor(glm::vec4 inputcolor);
    void Update();

    void draw();
    void pick_shader(const std::string& name);
    bool alive = true;
    unsigned id;

    Material material;
    Transform transform;
    Mesh mesh;
    Texture texture;
    glm::vec4 color{1.0};
};
