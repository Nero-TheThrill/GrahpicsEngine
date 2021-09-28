#pragma once
#include "Mesh.h"

class ModelMesh : public Mesh
{
public:
    ModelMesh();
    void Init() override;
    void Bind() override;
    void UnBind() override;
    void Draw() override;
    ~ModelMesh() override;
    void GeneratePositionsWithIndices();
    void GenerateNormals();
    void GenerateNormalLines();
    void BindData();
    void UnBindData();
    void ChangeMode(int mode) override;
    void DrawNormals() override;
    
private:
    GLuint VAO;
    GLuint VBO_positions, VBO_normals, VBO_texcoords;
    GLuint EBO;
    int index_size;
};

