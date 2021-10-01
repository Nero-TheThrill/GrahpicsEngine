#pragma once
#include <string>
#include "Material.h"
#include "MeshGroup.h"
#include "Texture.h"
#include "Transform.h"

class Object
{
public:
    Object(std::string n);
    Object(std::string n, Object* obj);
    ~Object();
    void SetColor(glm::vec3 inputcolor);
    void SetMeshGroup(MeshGroup* input);
    void Update();
    void SetShader(std::string id);
    void Draw();
    bool alive = true;
    unsigned id;
    int drawmode = 0;// 0: facenormal 1: vertexnormal
    bool shouldDrawNormals = false;
    Transform transform;
    MeshGroup* mesh;
    Shader shader, draw_normal_shader;
    Texture texture;
    glm::vec3 color{ 1.0 };
    std::string name;
};
