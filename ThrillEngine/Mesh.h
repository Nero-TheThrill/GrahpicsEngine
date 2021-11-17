#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Component.h"
#include "Shader.h"
#include "Material.h"

class Mesh : public Component
{
public:
    virtual void Init()=0;
    virtual void Bind()=0;
    virtual void Draw(Shader shader)=0;
    virtual void UnBind()=0;
    virtual void UnBindData();
    virtual void BindData();
    virtual ~Mesh();
    virtual void ChangeMode(int mode);
    virtual void DrawNormals();
    void SetMaterial(Material* mat);
    std::vector<glm::vec3> positions_use_indices;
    std::vector<glm::vec2> texcoords_use_indices;


    std::vector<glm::vec2> planar_texcoords_use_indices;
    std::vector<glm::vec2> spherical_texcoords_use_indices;
    std::vector<glm::vec2> cylindrical_texcoords_use_indices;

    std::vector<glm::vec2> planar_texcoords_use_indices_with_vertex_normal;
    std::vector<glm::vec2> spherical_texcoords_use_indices_with_vertex_normal;
    std::vector<glm::vec2> cylindrical_texcoords_use_indices_with_vertex_normal;



    std::vector<glm::vec3> face_normals;
    std::vector<glm::vec3> vertex_normals;

    std::vector<int> indices;

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texcoords;


    std::vector<glm::vec2> planar_texcoords;
    std::vector<glm::vec2> spherical_texcoords;
    std::vector<glm::vec2> cylindrical_texcoords;


    std::vector<glm::vec2> planar_texcoords_with_face_normal;
    std::vector<glm::vec2> spherical_texcoords_with_face_normal;
    std::vector<glm::vec2> cylindrical_texcoords_with_face_normal;

    std::vector<glm::vec3> face_normal_lines;
    std::vector<glm::vec3> vertex_normal_lines;
    float maxYval, minYval;
    int face_stride=0;
    std::string name;
    int n_mode = 0; // 0 : face  1 : vertex
    int mapping_mode = 0; // 0: default, 1: spherical, 2: cylindrical, 3: planar
    bool should_calculate_uv_in_gpu = true;
    bool mapping_with_normal = false;
    Material* material=nullptr;
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
}

inline void Mesh::ChangeMode(int mode)
{
}

inline void Mesh::DrawNormals()
{
}

inline void Mesh::SetMaterial(Material* mat)
{
    material = mat;
}

