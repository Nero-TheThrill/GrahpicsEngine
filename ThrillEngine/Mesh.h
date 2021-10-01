#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Component.h"

class Mesh : public Component
{
public:
    virtual void Init()=0;
    virtual void Bind()=0;
    virtual void Draw()=0;
    virtual void UnBind()=0;
    virtual void UnBindData();
    virtual void BindData();
    virtual ~Mesh();
    virtual void ChangeMode(int mode);
    virtual void DrawNormals();
    std::vector<glm::vec3> positions_use_indices;
    std::vector<glm::vec2> texcoords_use_indices;
    std::vector<glm::vec3> face_normals;
    std::vector<glm::vec3> vertex_normals;

    std::vector<int> indices;
    std::vector<int> normal_indices;
    std::vector<int> texture_indices;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texcoords;

    std::vector<glm::vec3> face_normal_lines;
    std::vector<glm::vec3> vertex_normal_lines;

    std::vector<glm::vec3> positions_normals;//use indices
    int face_stride=0;
    std::string name;
    int n_mode = 0; // 0 : face  1 : vertex
};

inline void Mesh::UnBindData()
{
}

inline void Mesh::BindData()
{
}

inline Mesh::~Mesh()
{
    positions_use_indices.clear();
    texcoords_use_indices.clear();
    texcoords.clear();
    vertex_normals.clear();
    face_normals.clear();
    vertex_normal_lines.clear();
    face_normal_lines.clear();
    indices.clear();
    positions.clear();
    positions_normals.clear();
}

inline void Mesh::ChangeMode(int mode)
{
}

inline void Mesh::DrawNormals()
{
}

