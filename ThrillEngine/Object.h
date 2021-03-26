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
    void SetColor(glm::vec4 color);
    void Update();

    void draw();
    void pick_shader(const std::string& name);
    bool alive = true;
    unsigned id;

    Material material;
    Transform transform;
    Mesh mesh;
    Texture texture;
};
