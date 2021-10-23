#include "ModelMesh.h"
#include <unordered_set>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
#include  "glm/gtx/hash.hpp"
#include "UVGenerator.h"
ModelMesh::ModelMesh()
{
    material=nullptr;
    VBO_positions = 0;
    VBO_normals = 0;
    EBO = 0;
    index_size = 0;
    VBO_texcoords = 0;
}

void ModelMesh::Init()
{
    if (!positions_use_indices.empty()&&!indices.empty())
    {
        GeneratePositionsWithIndices();
        GenerateNormals();
        GenerateNormalLines();
        GenerateTexcoords();
        glGenBuffers(1, &VBO_positions);
        glGenBuffers(1, &EBO);
    }
    if (!vertex_normals.empty())
    {
        glGenBuffers(1, &VBO_normals);
    }
    glGenBuffers(1, &VBO_texcoords);


    BindData();

}

void ModelMesh::Bind()
{
    if (!positions.empty() || !positions_use_indices.empty())
    {
        glEnableVertexAttribArray(0);
    }
    if (!face_normals.empty() || !vertex_normals.empty())
    {
        glEnableVertexAttribArray(1);
    }
    if (mapping_mode == 0 && (!texcoords.empty() || !texcoords_use_indices.empty()) || mapping_mode != 0)
    {
        glEnableVertexAttribArray(2);
    }
}

void ModelMesh::UnBind()
{
    if (!positions.empty()||!positions_use_indices.empty())
    {
        glDisableVertexAttribArray(0);
    }
    if (!face_normals.empty()||!vertex_normals.empty())
    {
        glDisableVertexAttribArray(1);
    }
    if (mapping_mode == 0 && (!texcoords.empty() || !texcoords_use_indices.empty()) || mapping_mode != 0)
    {
        glDisableVertexAttribArray(2);
    }
}

void ModelMesh::Draw(Shader shader)
{
    BindData();
    shader.set("maxYval", maxYval);
    shader.set("minYval", minYval);
    shader.set("mapping_mode", mapping_mode);
    shader.set("should_use_gpuside_uv", should_calculate_uv_in_gpu);
    shader.set("mapping_with_normal", mapping_with_normal);
    if (n_mode == 0)
    {

        glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(positions.size()));

    }
    else if (n_mode == 1)
    {

        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);

    }
    UnBindData();
}

ModelMesh::~ModelMesh()
{
    glDeleteBuffers(1, &VBO_positions);
    glDeleteBuffers(1, &VBO_normals);
    glDeleteBuffers(1, &VBO_texcoords);
    glDeleteBuffers(1, &EBO);

}

void ModelMesh::GeneratePositionsWithIndices()
{
    for (int i = 0; i < static_cast<int>(indices.size()); i++)
    {
        positions.push_back(positions_use_indices[indices[i]]);
    }
    if (!texcoords_use_indices.empty())
    {
        for (int i = 0; i < static_cast<int>(indices.size()); i++)
        {
            texcoords.push_back(texcoords_use_indices[indices[i]]);
        }
    }


}

void ModelMesh::GenerateNormals()
{
    std::unordered_set <glm::vec3> hvec;
    bool doesnt_have_vnorm = vertex_normals.empty();
    if (doesnt_have_vnorm)
    {
        for (auto p : positions_use_indices)
            vertex_normals.push_back(glm::vec3(0));
    }

    for (int i = 0; i < static_cast<int>(positions.size()); i +=3)
    {
        glm::vec3 v1 = positions[i],
            v2 = positions[i+static_cast<int64_t>(1)],  /* I use static_cast because of "Warning	C26451	Arithmetic overflow : Using operator '+' on a 4 byte value and then casting the result to a 8 byte value.Cast the value to the wider type before calling operator '+' to avoid overflow(io.2)" */
            v3 = positions[i+ static_cast<int64_t>(2)];
        glm::vec3 cross_result = glm::normalize(glm::cross(v2 - v1, v3 - v1));
        cross_result = glm::vec3(cross_result.x == 0.f ? 0 : cross_result.x, cross_result.y == 0.f ? 0 : cross_result.y, cross_result.z == 0.f ? 0 : cross_result.z);
        for (int j = 0; j < 3; j++)
        {
            face_normals.push_back(cross_result);
            if (doesnt_have_vnorm)
            {
                float key = static_cast<float>((indices[i + static_cast<int64_t>(j)] + 1)) * 10.f;
                glm::vec3 keyvalue = glm::vec3(cross_result.x + key, cross_result.y + key, cross_result.z + key);
                if (hvec.find(keyvalue) == hvec.end())
                {
                    hvec.insert(keyvalue);
                    vertex_normals[indices[i + static_cast<int64_t>(j)]] += cross_result;
                }
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
        vertex_normal_lines.push_back(glm::vec3(positions_use_indices[i]+ vertex_normals[i] / 10.f));
    }
    for (int i = 0; i < static_cast<int>(positions.size()); i+=3)
    {
        glm::vec3 midpoint=glm::vec3(0);
        for (int j = 0; j < 3; j++)
        {
            midpoint += positions[i + static_cast<int64_t>(j)];
        }
        midpoint /= 3;

        face_normal_lines.push_back(midpoint);
        face_normal_lines.push_back(midpoint + face_normals[i]/10.f);
    }
}

void ModelMesh::GenerateTexcoords()
{
    
    for (int i = 0; i < static_cast<int>(indices.size()); i++)
    {
        spherical_texcoords.push_back(spherical_texcoords_use_indices[indices[i]]);
    }
    for (int i = 0; i < static_cast<int>(indices.size()); i++)
    {
        cylindrical_texcoords.push_back(cylindrical_texcoords_use_indices[indices[i]]);
    }
    for (int i = 0; i < static_cast<int>(indices.size()); i++)
    {
        planar_texcoords.push_back(planar_texcoords_use_indices[indices[i]]);
    }
}

void ModelMesh::BindData()
{
    if (n_mode == 0)
    {
        if (!positions.empty())
        {
            glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * positions.size()), positions.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);
        }
        if (!face_normals.empty())
        {
            glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * face_normals.size()), &face_normals[0], GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(1);
        }
        if (mapping_mode == 0)
        {
            if (!texcoords_use_indices.empty())
            {
                glBindBuffer(GL_ARRAY_BUFFER, VBO_texcoords);
                glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 2 * texcoords.size()), texcoords.data(), GL_STATIC_DRAW);
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
                glEnableVertexAttribArray(2);
            }
        }
        else
        {
            glBindBuffer(GL_ARRAY_BUFFER, VBO_texcoords);
            if (mapping_mode == 1)
                glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 2 * spherical_texcoords.size()), spherical_texcoords.data(), GL_STATIC_DRAW);
            else if (mapping_mode == 2)
                glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 2 * cylindrical_texcoords.size()), cylindrical_texcoords.data(), GL_STATIC_DRAW);
            else
                glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 2 * planar_texcoords.size()), planar_texcoords.data(), GL_STATIC_DRAW);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(2);
        }
    }
    else if (n_mode == 1)
    {
        if (!positions_use_indices.empty()&&!indices.empty())
        {
            glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * positions_use_indices.size()), &positions_use_indices[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);


            if (!vertex_normals.empty())
            {
                glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
                glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * vertex_normals.size()), &vertex_normals[0], GL_STATIC_DRAW);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
                glEnableVertexAttribArray(1);
            }
            if (mapping_mode == 0)
            {
                if (!texcoords_use_indices.empty())
                {
                    glBindBuffer(GL_ARRAY_BUFFER, VBO_texcoords);
                    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 2 * texcoords_use_indices.size()), texcoords_use_indices.data(), GL_STATIC_DRAW);
                    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
                    glEnableVertexAttribArray(2);
                }
            }
            else
            {
                glBindBuffer(GL_ARRAY_BUFFER, VBO_texcoords);
                if(mapping_mode==1)
                    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 2 * spherical_texcoords_use_indices.size()), spherical_texcoords_use_indices.data(), GL_STATIC_DRAW);
                else if(mapping_mode==2)
                    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 2 * cylindrical_texcoords_use_indices.size()), cylindrical_texcoords_use_indices.data(), GL_STATIC_DRAW);
                else
                    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 2 * planar_texcoords_use_indices.size()), planar_texcoords_use_indices.data(), GL_STATIC_DRAW);
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
                glEnableVertexAttribArray(2);
            }

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(int) * indices.size()), &indices[0], GL_STATIC_DRAW);
         
        }
    }
}

void ModelMesh::UnBindData()
{
    if (!positions.empty() || !positions_use_indices.empty())
    {
        glDisableVertexAttribArray(0);
    }
    if (!face_normals.empty() || !vertex_normals.empty())
    {
        glDisableVertexAttribArray(1);
    }
    if (mapping_mode == 0&&(!texcoords.empty() || !texcoords_use_indices.empty())||mapping_mode!=0)
    {
        glDisableVertexAttribArray(2);
    }
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

void ModelMesh::DrawNormals()
{
    if (!positions_use_indices.empty() && !indices.empty())
    {
        if (n_mode == 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeof(float) * 3 * face_normal_lines.size()), &face_normal_lines[0], GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);

            glDrawArrays(GL_LINES, 0, static_cast<GLsizei>(face_normal_lines.size()));
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
}
