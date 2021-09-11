#include "Mesh.h"

Mesh::Mesh()
{
    VAO = 0;
    VBO_positions = 0;
    VBO_normals = 0;
    EBO = 0;
    index_size = 0;
}

void Mesh::Init()
{

    for(int i = 0; i < position_indices.size(); i++)
    {
        positions_.push_back(positions[position_indices[i]*3]);
        positions_.push_back(positions[position_indices[i]*3+1]);
        positions_.push_back(positions[position_indices[i]*3+2]);
    }
    for (int i = 0; i < positions_.size(); i += 9)
    {
        glm::vec3 v1 = glm::vec3(positions_[i], positions_[i+1], positions_[i+ 2]),
            v2 = glm::vec3(positions_[i+3], positions_[i + 4], positions_[i + 5]),
            v3 = glm::vec3(positions_[i + 6], positions_[i + 7], positions_[i + 8]);
        glm::vec3 cross_result = glm::cross(v2 - v1, v3 - v1);
        normals.push_back(cross_result.x);
        normals.push_back(cross_result.y);
        normals.push_back(cross_result.z);
        normals.push_back(cross_result.x);
        normals.push_back(cross_result.y);
        normals.push_back(cross_result.z);
        normals.push_back(cross_result.x);
        normals.push_back(cross_result.y);
        normals.push_back(cross_result.z);
    }
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // position attribute
    glGenBuffers(1, &VBO_positions);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*positions_.size(), &positions_[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint)*position_indices.size(), &position_indices[0], GL_STATIC_DRAW);

  

    //normal
    glGenBuffers(1, &VBO_normals);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), &normals[0], GL_STATIC_DRAW);

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
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)positions_.size());
    //glDrawElements(GL_TRIANGLES,(GLsizei)position_indices.size(), GL_UNSIGNED_INT, nullptr);
    UnBind();
}

void Mesh::UnBind()
{
    glBindVertexArray(0);  
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_positions);
    glDeleteBuffers(1, &VBO_normals);
    glDeleteBuffers(1, &EBO);
}
                                                            