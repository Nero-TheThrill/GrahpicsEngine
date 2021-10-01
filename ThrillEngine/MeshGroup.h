#pragma once
#include <vector>
#include <glad/glad.h>

#include "ModelMesh.h"

class MeshGroup
{
public:
    MeshGroup();
    void Init();
    void Draw();
    void DrawNormals();
    void ChangeMode(int mode);
    void AddMesh(Mesh* mesh);
    ~MeshGroup();
    std::string name;
    int n_mode;
private:
    GLuint VAO;
    std::vector<Mesh*> model_meshes;
};


