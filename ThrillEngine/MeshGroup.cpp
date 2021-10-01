#include "MeshGroup.h"

MeshGroup::MeshGroup()
{
    n_mode = 0;
    VAO = 0;
}

void MeshGroup::Init()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    for (auto mesh : model_meshes)
        mesh->Init();

    std::cout << "ModelMesh <" << name << "> Initialized" << std::endl;
}

void MeshGroup::Draw()
{

    for(auto mesh: model_meshes)
    {
        glBindVertexArray(VAO);
        mesh->Draw();
        glBindVertexArray(0);
    }
}

void MeshGroup::DrawNormals()
{
    for (auto mesh : model_meshes)
    {
        glBindVertexArray(VAO);
        mesh->DrawNormals();
        glBindVertexArray(0);
    }
}

void MeshGroup::ChangeMode(int mode)
{
    if (mode != n_mode)
    {
        for (auto mesh : model_meshes)
        {
            n_mode = mode;
            mesh->n_mode = mode;
            glBindVertexArray(0);
            mesh->UnBindData();
            glBindVertexArray(VAO);
            mesh->BindData();
        }
    }
}

void MeshGroup::AddMesh(Mesh* mesh)
{
    model_meshes.push_back(mesh);
}

MeshGroup::~MeshGroup()
{
    glDeleteVertexArrays(1, &VAO);
    for (auto mesh : model_meshes)
    {
        delete mesh;
        mesh = nullptr;
    }
}
