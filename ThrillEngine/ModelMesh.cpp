#include "ModelMesh.h"
#include <unordered_set>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

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
    GenerateVertexNormals();
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



        /*  vertex normals

    glGenBuffers(1, &VBO_positions);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * positions_use_indices.size()), &positions_use_indices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &VBO_normals);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float)* 3 * vertex_normals.size()), &vertex_normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(int) * indices.size()), &indices[0], GL_STATIC_DRAW);


    ////
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()*3),GL_UNSIGNED_INT,(void*)0 );
     */
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


    for (int i = 0; i < static_cast<int>(indices.size()); i++)
    {
        positions.push_back(positions_use_indices[indices[i]]);
    }

}

void ModelMesh::GenerateFaceNormals()
{
    glm::vec3 v;
    std::unordered_set <std::string> hvec;
    for (auto p : positions_use_indices)
        vertex_normals.push_back(glm::vec3(0));
    for (int i = 0; i < static_cast<int>(positions.size()); i +=face_stride)
    {
        glm::vec3 v1 = positions[i],
            v2 = positions[i+1],
            v3 = positions[i+2];
        glm::vec3 cross_result = glm::normalize(glm::cross(v2 - v1, v3 - v1));
        for (int j = 0; j < face_stride; j++)
        {
            face_normals.push_back(cross_result);
            std::string vstring = std::to_string(indices[i] + j) + "/" + glm::to_string(cross_result);
            if (hvec.find(vstring)== hvec.end())
            {
                hvec.insert(vstring);
                vertex_normals[indices[i+j]] += cross_result;
            }
        }
    }
}

void ModelMesh::GenerateVertexNormals()
{

}
