#include "SphereMesh.h"
#include <unordered_set>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

SphereMesh::SphereMesh()
{
    VBO_positions = 0;
    VBO_normals = 0;
    VBO_texcoords = 0;
    EBO = 0;
    index_size = 0;
}

void SphereMesh::Init()
{
    for (int i = 0; i < static_cast<int>(indices.size()); i++)
    {
        positions.push_back(positions_use_indices[indices[i]]);
        texcoords.push_back(texcoords_use_indices[indices[i]]);
    }
    GenerateNormals();
    GenerateNormalLines();
    glGenBuffers(1, &VBO_positions);
    glGenBuffers(1, &VBO_normals);
    glGenBuffers(1, &VBO_texcoords);
    glGenBuffers(1, &EBO);
    BindData();
   
    std::cout << "SphereMesh <" << name << "> Initialized" << std::endl;
}

void SphereMesh::Bind()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void SphereMesh::UnBind()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void SphereMesh::Draw()
{
    Bind();
    if (n_mode == 0)
        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size()));
    else if( n_mode==1)
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
    UnBind();
}

void SphereMesh::GenerateNormals()
{
    for (int i = 0; i < static_cast<int>(positions.size()); i += 3)
    {
        glm::vec3 v1 = positions[i],
            v2 = positions[i + static_cast<int64_t>(1)],
            v3 = positions[i + static_cast<int64_t>(2)];
        glm::vec3 cross_result = glm::normalize(glm::cross(v2 - v1, v3 - v1));
        for (int j = 0; j < 3; j++)
        {
            face_normals.push_back(cross_result);
        }
    }
}

void SphereMesh::GenerateNormalLines()
{
    for (int i = 0; i < static_cast<int>(positions_use_indices.size()); i++)
    {
        vertex_normal_lines.push_back(positions_use_indices[i]);
        vertex_normal_lines.push_back(positions_use_indices[i] + vertex_normals[i]/10.f);
    }
    for (int i = 0; i < static_cast<int>(positions.size()); i += 3)
    {
        glm::vec3 midpoint = glm::vec3(0);
        for (int j = 0; j < 3; j++)
        {
            midpoint += positions[i + static_cast<int64_t>(j)];
        }
        midpoint /= 3;

        face_normal_lines.push_back(midpoint);
        face_normal_lines.push_back(midpoint + face_normals[i]/10.f);
    }
}

SphereMesh::~SphereMesh()
{
    glDeleteBuffers(1, &VBO_positions);
    glDeleteBuffers(1, &VBO_normals);
    glDeleteBuffers(1, &VBO_texcoords);
    glDeleteBuffers(1, &EBO);
    std::cout << "SphereMesh <" << name << "> Destructor Called" << std::endl;
}

void SphereMesh::ChangeMode(int mode)
{
    if (mode != n_mode)
    {
        n_mode = mode;
        UnBindData();
        BindData();
    }
}

void SphereMesh::UnBindData()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    if (!texcoords_use_indices.empty())
    {
        glDisableVertexAttribArray(2);
    }
}

void SphereMesh::BindData()
{
    if (n_mode == 0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * positions.size()), &positions[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * face_normals.size()), &face_normals[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_texcoords);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 2 * texcoords.size()), &texcoords[0], GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    }
    else if (n_mode == 1)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * positions_use_indices.size()), &positions_use_indices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


        glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * vertex_normals.size()), &vertex_normals[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, VBO_texcoords);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 2 * texcoords_use_indices.size()), &texcoords_use_indices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(int) * indices.size()), &indices[0], GL_STATIC_DRAW);
    }
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void SphereMesh::DrawNormals()
{
    if (n_mode == 0)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * face_normal_lines.size()), &face_normal_lines[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(face_normal_lines.size()*2));
    }
    else if (n_mode == 1)
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * vertex_normal_lines.size()), &vertex_normal_lines[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(vertex_normal_lines.size()));
    }
    glDisableVertexAttribArray(0);

    BindData();
}
