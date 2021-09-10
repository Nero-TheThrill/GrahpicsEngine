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
    void SetColor(glm::vec3 inputcolor);
    void Update();

    void draw();
    void pick_material(const std::string& material_id);
    bool alive = true;
    unsigned id;

    Material material;
    Transform transform;
    Mesh mesh;
    Texture texture;
    glm::vec3 color{1.0};
};
