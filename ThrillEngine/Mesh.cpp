#include "Mesh.h"

#include <iostream>

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
    
    if (drawmode == DrawMode::MODEL)
    {
        float min_val_x = positions_use_indices[0];
        float max_val_x = min_val_x;
        float max_val_y = min_val_x, min_val_y = min_val_x;
        float max_val_z = min_val_x, min_val_z = min_val_x;
        int iterator = 0;
        for (auto p : positions_use_indices)
        {
            if (iterator % 3 == 0)
            {
                min_val_x = std::min(p, min_val_x);
                max_val_x = std::max(p, max_val_x);
            }
            else if (iterator % 3 == 1)
            {
                min_val_y = std::min(p, min_val_y);
                max_val_y = std::max(p, max_val_y);
            }
            else
            {
                min_val_z = std::min(p, min_val_z);
                max_val_z = std::max(p, max_val_z);
            }


            iterator++;
        }
        float denominator = std::max(std::max(max_val_x - min_val_x, max_val_y - min_val_y), max_val_z - min_val_z) / 2.f;
        float gap_x = max_val_x - min_val_x;
        float gap_y = max_val_y - min_val_y;
        float gap_z = max_val_z - min_val_z;
        float subtract_x = gap_x / 2.f + min_val_x;
        float subtract_y = gap_y / 2.f + min_val_y;
        float subtract_z = gap_z / 2.f + min_val_z;
        iterator = 0;
        for (auto p : positions_use_indices)
        {
            if (iterator % 3 == 0)
                positions_use_indices[iterator] = (p - subtract_x) / denominator;
            else if (iterator % 3 == 1)
                positions_use_indices[iterator] = (p - subtract_y) / denominator;
            else
                positions_use_indices[iterator] = (p - subtract_z) / denominator;

            iterator++;
        }
        for (int i = 0; i < position_indices.size(); i++)
        {
            positions.push_back(positions_use_indices[position_indices[i] * 3]);
            positions.push_back(positions_use_indices[position_indices[i] * 3 + 1]);
            positions.push_back(positions_use_indices[position_indices[i] * 3 + 2]);
        }
        for (int i = 0; i < positions.size(); i += 3*face_stride)
        {
            glm::vec3 v1 = glm::vec3(positions[i], positions[i + 1], positions[i + 2]),
                v2 = glm::vec3(positions[i + 3], positions[i + 4], positions[i + 5]),
                v3 = glm::vec3(positions[i + 6], positions[i + 7], positions[i + 8]);
            glm::vec3 cross_result = glm::cross(v2 - v1, v3 - v1);
            for (int j = 0; j < face_stride; j++)
            {
                normals.push_back(cross_result.x);
                normals.push_back(cross_result.y);
                normals.push_back(cross_result.z);
            }
        }
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // position attribute
        glGenBuffers(1, &VBO_positions);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions.size(), &positions[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &VBO_normals);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), &normals[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(1);


        //// texture coord attribute
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        //glEnableVertexAttribArray(2);
    }
    else if (drawmode == DrawMode::SPHERE)
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);


        glGenBuffers(1, &VBO_positions);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions_normals_use_indices.size(), &positions_normals_use_indices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);


        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * position_indices.size(), &position_indices[0], GL_STATIC_DRAW);

    }
}

void Mesh::Bind()
{
    glBindVertexArray(VAO);
}

void Mesh::Draw()
{
    Bind();
    if(drawmode== DrawMode::MODEL)
    {
        if (face_stride == 3)
            glDrawArrays(GL_TRIANGLES, 0, (GLsizei)positions.size());
        else if (face_stride > 3)
            glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei)positions.size());
    }

    else if(drawmode== DrawMode::SPHERE)
        glDrawElements(GL_TRIANGLES,(GLsizei)position_indices.size(), GL_UNSIGNED_INT, (void*)0);
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
