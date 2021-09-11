#include "Mesh.h"

Mesh::Mesh()
{
    VAO = 0;
    VBO = 0;
    EBO = 0;
    index_size = 0;
}

void Mesh::Init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*positions.size(), &positions[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)*position_indices.size(), &position_indices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    ////normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);

    //// texture coord attribute
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);

}

void Mesh::Bind()
{
    glBindVertexArray(VAO);
}

void Mesh::Draw()
{
    Bind();
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES,(GLsizei)position_indices.size(), GL_UNSIGNED_INT, nullptr);
    UnBind();
}

void Mesh::UnBind()
{
    glBindVertexArray(0);  
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
                                                            