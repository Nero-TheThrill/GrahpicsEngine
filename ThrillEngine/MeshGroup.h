#pragma once
#include <vector>
#include <glad/glad.h>

#include "ModelMesh.h"

class MeshGroup
{
public:
    MeshGroup();
    void Init();
    void Draw(Shader shader,Material* custom_material=nullptr);
    void DrawNormals();
    void ChangeMode(int mode);
    void AddMesh(Mesh* mesh);
    void SetMaterial(Material* m);
    ~MeshGroup();
    std::string name;
    int n_mode=0; // 0: face normal,  1: vertex normal
    int mapping_mode=0; // 0: default, 1: spherical, 2: cylindrical, 3: planar
    bool should_calculate_uv_in_gpu=true;
    bool mapping_with_normal = false;
    std::vector<Mesh*> model_meshes;
private:
    GLuint VAO;

};


