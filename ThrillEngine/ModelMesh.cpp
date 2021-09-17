#include "ModelMesh.h"
#include <unordered_set>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include  "glm/gtx/hash.hpp"

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
    GeneratePositionsWithIndices();
    GenerateNormals();
    GenerateNormalLines();
    BindData();
    std::cout << "ModelMesh <" << name << "> Initialized" << std::endl;
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
    if (n_mode == 0)
    {
        if (face_stride == 3)
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size() * 3));
        else if (face_stride > 3)
            glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(positions.size() * 3));
    }
    else if(n_mode==1)
    {
         if (face_stride == 3)
             glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size() * 3), GL_UNSIGNED_INT, (void*)0);
         else if (face_stride > 3)
             glDrawElements(GL_TRIANGLE_FAN, static_cast<GLsizei>(indices.size() * 3), GL_UNSIGNED_INT, (void*)0);
    }
    UnBind();
    if(shouldDrawNormals)
    {
        UnBindData();
        if (n_mode == 0)
        {
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO_positions);
            glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * face_normal_lines.size()), &face_normal_lines[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(0);

            glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(face_normal_lines.size() * 3));
        }
        else if (n_mode == 1)
        {
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glGenBuffers(1, &VBO_positions);
            glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * vertex_normal_lines.size()), &vertex_normal_lines[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(0);

            glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(vertex_normal_lines.size() * 3));
        }
        UnBindData();
        BindData();
    }
}

ModelMesh::~ModelMesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_positions);
    glDeleteBuffers(1, &VBO_normals);
    glDeleteBuffers(1, &EBO);
    std::cout << "ModelMesh <" << name << "> Destructor Called" << std::endl;
}

void ModelMesh::GeneratePositionsWithIndices()
{
    for (int i = 0; i < static_cast<int>(indices.size()); i++)
    {
        positions.push_back(positions_use_indices[indices[i]]);
    }
}

void ModelMesh::GenerateNormals()
{
    std::unordered_set <glm::vec3> hvec;
    for (auto p : positions_use_indices)
        vertex_normals.push_back(glm::vec3(0));
    for (int i = 0; i < static_cast<int>(positions.size()); i +=face_stride)
    {
        glm::vec3 v1 = positions[i],
            v2 = positions[i+1],
            v3 = positions[i+2];
        glm::vec3 cross_result = glm::normalize(glm::cross(v2 - v1, v3 - v1));
        cross_result = glm::vec3(cross_result.x == 0.f ? 0 : cross_result.x, cross_result.y == 0.f ? 0 : cross_result.y, cross_result.z == 0.f ? 0 : cross_result.z);
        for (int j = 0; j < face_stride; j++)
        {
            face_normals.push_back(cross_result);
            float key = static_cast<float>((indices[i + j] + 1)) * 10.f;
            glm::vec3 keyvalue = glm::vec3(cross_result.x + key, cross_result.y + key, cross_result.z + key);
            if (hvec.find(keyvalue)== hvec.end())
            {
                hvec.insert(keyvalue);
                vertex_normals[indices[i+j]] += cross_result;
            }
        }
    }
    int iterator = 0;
    for(auto n:vertex_normals)
    {
        vertex_normals[iterator] = glm::normalize(n);
        iterator++;
    }
}

void ModelMesh::GenerateNormalLines()
{

    for (int i = 0; i < static_cast<int>(positions_use_indices.size()); i++)
    {
        vertex_normal_lines.push_back(positions_use_indices[i]);
        vertex_normal_lines.push_back(positions_use_indices[i] + vertex_normals[i]);
    }
    for (int i = 0; i < static_cast<int>(positions.size()); i+=face_stride)
    {
        glm::vec3 midpoint=glm::vec3(0);
        for (int j = 0; j < face_stride; j++)
        {
            midpoint += positions[i + j];
        }
        midpoint /= face_stride;

        face_normal_lines.push_back(midpoint);
        face_normal_lines.push_back(midpoint + face_normals[i]);
    }
}

void ModelMesh::BindData()
{
    if (n_mode == 0)
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO_positions);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * positions.size()), &positions[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &VBO_normals);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * face_normals.size()), &face_normals[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);
        //// texture coord attribute
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        //glEnableVertexAttribArray(2);
    }
    else if (n_mode == 1)
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO_positions);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * positions_use_indices.size()), &positions_use_indices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &VBO_normals);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
        glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * vertex_normals.size()), &vertex_normals[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(int) * indices.size()), &indices[0], GL_STATIC_DRAW);
    }
}

void ModelMesh::UnBindData()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_positions);
    glDeleteBuffers(1, &VBO_normals);
    glDeleteBuffers(1, &EBO);
}

void ModelMesh::ChangeMode(int mode)
{
    if (mode != n_mode)
    {
        n_mode = mode;
        UnBindData();
        BindData();
    }
}
