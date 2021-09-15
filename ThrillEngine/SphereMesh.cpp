#include "SphereMesh.h"

SphereMesh::SphereMesh()
{
    VAO = 0;
    VBO_positions = 0;
    VBO_normals = 0;
    VBO_texcoords = 0;
    EBO = 0;
    index_size = 0;
}

void SphereMesh::Init()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    glGenBuffers(1, &VBO_positions);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float)*3 * positions.size()), &positions[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &VBO_normals);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * vertex_normals.size()), &vertex_normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glGenBuffers(1, &VBO_texcoords);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_texcoords);

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * texcoords.size()), &texcoords[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);




    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(int) * indices.size()), &indices[0], GL_STATIC_DRAW);
}

void SphereMesh::Bind()
{
    glBindVertexArray(VAO);
}

void SphereMesh::UnBind()
{
    glBindVertexArray(0);
}

void SphereMesh::Draw()
{
    Bind();
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()*3), GL_UNSIGNED_INT, (void*)0);
    UnBind();
}

SphereMesh::~SphereMesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_positions);
    glDeleteBuffers(1, &VBO_normals);
    glDeleteBuffers(1, &VBO_texcoords);
    glDeleteBuffers(1, &EBO);
}
