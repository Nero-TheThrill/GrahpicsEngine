#pragma once
#include "Mesh.h"

class LineMesh : public Mesh
{
public:
    LineMesh();
    void Init() override;
    void Bind() override;
    void UnBind() override;
    void Draw() override;
    ~LineMesh() override;
private:
    GLuint VBO_positions, VBO_normals;
    GLuint EBO;
    int index_size;
};

