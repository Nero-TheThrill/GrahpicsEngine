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
    void AdjustVerticesScale();
    void GenerateFaceNormals();
    void GenerateVertexNormals();

private:
    GLuint VAO;
    GLuint VBO_positions, VBO_normals;
    GLuint EBO;
    int index_size;
};

