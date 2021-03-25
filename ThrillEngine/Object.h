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
    void SetObject(const std::string& filepath, const std::string& shader_id);
    ~Object();
    void LoadObject(const std::string& path);
    void Update();

    void draw();
    void pick_shader(const std::string& name);
    bool alive = true;
    unsigned id;
private:

    Material material;
    Transform transform;
    Mesh mesh;
    Texture texture;



    //translate rotate scale... components needed
};
