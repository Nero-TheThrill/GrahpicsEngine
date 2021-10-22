#pragma once
#include "Mesh.h"
#include "Shader.h"

class SphereMesh : public Mesh
{
public:
    SphereMesh();
    void Init() override;
    void Bind() override;
    void UnBind() override;
    void Draw(Shader shader) override;
    void GenerateNormals();
    void GenerateNormalLines();
    ~SphereMesh() override;
    void ChangeMode(int mode) override;
    void UnBindData();
    void BindData();
    void DrawNormals() override;
private:
    GLuint VBO_positions, VBO_normals, VBO_texcoords;
    GLuint EBO;
    int index_size;
};

