#pragma once
#include "Mesh.h"

class SphereMesh : public Mesh
{
public:
    SphereMesh();
    void Init() override;
    void Bind() override;
    void UnBind() override;
    void Draw() override;
    ~SphereMesh() override;
private:
    GLuint VAO;
    GLuint VBO_positions, VBO_normals, VBO_texcoords;
    GLuint EBO;
    int index_size;
};

