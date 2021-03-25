#include "Object.h"
#include "Input.h"
#include "Material.h"
#include <iostream>
#include "stb_image.h"



void Object::LoadObject(const std::string& path)
{
    /*std::array<glm::vec2, 4> pos_vtx;
    pos_vtx[0] = glm::vec2(0.5f, -0.5f); pos_vtx[1] = glm::vec2(0.5f, 0.5f);
    pos_vtx[2] = glm::vec2(-0.5f, 0.5f); pos_vtx[3] = glm::vec2(-0.5f, -0.5f);
    std::array<glm::vec3, 4> clr_vtx;
    clr_vtx[0] = glm::vec3(1.f, 0.f, 0.f); clr_vtx[1] = glm::vec3(0.f, 1.f,
        0.f);
    clr_vtx[2] = glm::vec3(0.f, 0.f, 1.f); clr_vtx[3] = glm::vec3(1.f, 1.f,
        1.f);

    glCreateBuffers(1, &VBO);

    glNamedBufferStorage(VBO,
        sizeof(glm::vec2) * pos_vtx.size() + sizeof(glm::vec3) * clr_vtx.size(),
        nullptr, GL_DYNAMIC_STORAGE_BIT);
    glNamedBufferSubData(VBO, 0,
        sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());
    glNamedBufferSubData(VBO, sizeof(glm::vec2) * pos_vtx.size(),
        sizeof(glm::vec3) * clr_vtx.size(), clr_vtx.data());


    glCreateVertexArrays(1, &VAO);
    glEnableVertexArrayAttrib(VAO, 0);
    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(glm::vec2));
    glVertexArrayAttribFormat(VAO, 0, 2, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(VAO, 0, 0);
    glEnableVertexArrayAttrib(VAO, 1);
    glVertexArrayVertexBuffer(VAO, 1, VBO,
        sizeof(glm::vec2) * pos_vtx.size(), sizeof(glm::vec3));
    glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(VAO, 1, 1);

    std::array<GLushort, 6> idx_vtx;
    idx_vtx[0] = 0; idx_vtx[1] = 1; idx_vtx[2] = 2;
    idx_vtx[3] = 2; idx_vtx[4] = 3; idx_vtx[5] = 0;
    index_size = idx_vtx.size();
    GLuint ebo_hdl;
    glCreateBuffers(1, &ebo_hdl);
    glNamedBufferStorage(ebo_hdl,
        sizeof(GLushort) * idx_vtx.size(),
        reinterpret_cast<GLvoid*>(idx_vtx.data()),
        GL_DYNAMIC_STORAGE_BIT);

    glVertexArrayElementBuffer(VAO, ebo_hdl);
    glBindVertexArray(0);*/


    mesh.Init();
    texture.Init();
    transform.Init();
    

    material.Use();


    material.set("texture1", 0);
    material.set("texture2", 1);
    material.set("ourColor", glm::vec4(0, 1, 1, 1));
    material.UnUse();
}

void Object::Update()
{
    draw();
}

Object::Object()
{

    id = 0;
}


void Object::SetObject(const std::string& filepath, const std::string& shader_id)
{
    pick_shader(shader_id);
    LoadObject(filepath);

}

Object::~Object()
{
}

void Object::draw()
{
    transform.Rotate((float)glfwGetTime() * 50.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    


    material.Use();
    material.set("model", transform.GetTransformMatrix());
    mesh.Draw();
    material.UnUse();

    //material.Use();
    //glBindVertexArray(VAO);
    //glDrawElements(GL_TRIANGLES, index_size, GL_UNSIGNED_SHORT, NULL);
    //glBindVertexArray(0);
    //material.UnUse();
}

void Object::pick_shader(const std::string& name)
{
    material.SetProgramHandle(name);
}

