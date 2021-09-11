#pragma once
#include <string>
#include "Material.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

class Object
{
public:
    Object(std::string n);
    Object(std::string n, Object* obj);
    ~Object();
    void SetColor(glm::vec3 inputcolor);
    void SetMesh(Mesh* input);
    void Update();

    void Draw();
    void Pick_Material(const std::string& material_id);
    bool alive = true;
    unsigned id;

    Material* material;
    Transform transform;
    Mesh* mesh;
    Texture texture;
    glm::vec3 color{1.0};
    std::string name;
};
