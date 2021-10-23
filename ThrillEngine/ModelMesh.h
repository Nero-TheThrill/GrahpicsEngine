#pragma once
#include "Material.h"
#include "Mesh.h"

class ModelMesh : public Mesh
{
public:
    ModelMesh();
    void Init() override;
    void Bind() override;
    void UnBind() override;
    void Draw(Shader shader) override;
    ~ModelMesh() override;
    void GeneratePositionsWithIndices();
    void GenerateNormals();
    void GenerateNormalLines();
    void GenerateTexcoords();
    void BindData();
    void UnBindData();
    void ChangeMode(int mode) override;
    void DrawNormals() override;
private:
    Material* material;
    GLuint VBO_positions, VBO_normals, VBO_texcoords;
    GLuint EBO;
    int index_size;
};

