#include "LineMesh.h"

LineMesh::LineMesh()
{
    VAO = 0;
    VBO_positions = 0;
    VBO_normals = 0;
    EBO = 0;
    index_size = 0;
}

void LineMesh::Init()
{
    for(int i=0;i<1000;i++)
    {
        glm::vec3 input1 = glm::vec3(cos(static_cast<float>(i) / 50.f), 0, sin(static_cast<float>(i) / 50.f));
        glm::vec3 input2 = glm::vec3(cos(static_cast<float>(i+1) / 50.f), 0, sin(static_cast<float>(i+1) / 50.f));
        positions.push_back(input1);
        positions.push_back(input2);
    }



    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);


    glGenBuffers(1, &VBO_positions);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * positions.size()), &positions[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

}

void LineMesh::Bind()
{
    glBindVertexArray(VAO);
}

void LineMesh::UnBind()
{
    glBindVertexArray(0);
}

void LineMesh::Draw()
{
    Bind();
    glDrawArrays(GL_LINES,0, static_cast<GLsizei>(positions.size()));
    UnBind();
}

LineMesh::~LineMesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_positions);
    glDeleteBuffers(1, &VBO_normals);
    glDeleteBuffers(1, &EBO);
}
