#define GLM_ENABLE_EXPERIMENTAL
#include "ModelMesh.h"
#include "glm/gtx/hash.hpp"
#include <unordered_map>

ModelMesh::ModelMesh()
{
    VAO = 0;
    VBO_positions = 0;
    VBO_normals = 0;
    EBO = 0;
    index_size = 0;
}

void ModelMesh::Init()
{
    AdjustVerticesScale();
    GenerateFaceNormals();
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // position attribute
    glGenBuffers(1, &VBO_positions);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * positions.size()), &positions[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &VBO_normals);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float)* 3 * face_normals.size()), &face_normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);


    //// texture coord attribute
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);
}

void ModelMesh::Bind()
{
    glBindVertexArray(VAO);
}

void ModelMesh::UnBind()
{
    glBindVertexArray(0);
}

void ModelMesh::Draw()
{
    Bind();
    if (face_stride == 3)
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size()*3));
    else if (face_stride > 3)
        glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(positions.size()*3));
    UnBind();
}

ModelMesh::~ModelMesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_positions);
    glDeleteBuffers(1, &VBO_normals);
    glDeleteBuffers(1, &EBO);
}

void ModelMesh::AdjustVerticesScale()
{
    float min_val_x = positions_use_indices[0].x;
    float max_val_x = min_val_x;
    float max_val_y = min_val_x, min_val_y = min_val_x;
    float max_val_z = min_val_x, min_val_z = min_val_x;
    int iterator = 0;
    for (auto p : positions_use_indices)
    {

        min_val_x = std::min(p.x, min_val_x);
        max_val_x = std::max(p.x, max_val_x);

        min_val_y = std::min(p.y, min_val_y);
        max_val_y = std::max(p.y, max_val_y);

        min_val_z = std::min(p.z, min_val_z);
        max_val_z = std::max(p.z, max_val_z);

        iterator++;
    }
    float gap_x = max_val_x - min_val_x;
    float gap_y = max_val_y - min_val_y;
    float gap_z = max_val_z - min_val_z;
    float denominator = std::max(std::max(gap_x, gap_y), gap_z) / 2.f;

    float subtract_x = gap_x / 2.f + min_val_x;
    float subtract_y = gap_y / 2.f + min_val_y;
    float subtract_z = gap_z / 2.f + min_val_z;
    iterator = 0;
    for (auto p : positions_use_indices)
    {
        positions_use_indices[iterator] = glm::vec3((p.x - subtract_x) / denominator,(p.y - subtract_y) / denominator,(p.z - subtract_z) / denominator);
        iterator++;
    }
    for (int i = 0; i < static_cast<int>(indices.size()); i++)
    {
        positions.push_back(positions_use_indices[indices[i]]);
    }
}

void ModelMesh::GenerateFaceNormals()
{
    for (int i = 0; i < static_cast<int>(positions.size()); i +=face_stride)
    {
        glm::vec3 v1 = positions[i],
            v2 = positions[i+1],
            v3 = positions[i+2];
        glm::vec3 cross_result = glm::cross(v2 - v1, v3 - v1);
        for (int j = 0; j < face_stride; j++)
        {
            face_normals.push_back(cross_result);
        }
    }
}

void ModelMesh::GenerateVertexNormals()
{
    std::unordered_map<glm::vec3, int> check_already_added;
    check_already_added.clear();
}
