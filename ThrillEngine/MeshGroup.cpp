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

void MeshGroup::Draw(Shader shader)
{
    for(auto mesh: model_meshes)
    {
        mesh->should_calculate_uv_in_gpu = should_calculate_uv_in_gpu;
        mesh->mapping_mode = mapping_mode;
        mesh->mapping_with_normal = mapping_with_normal;
        glBindVertexArray(VAO);
        mesh->Draw(shader);
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

void MeshGroup::SetMaterial(Material* m)
{
    for (auto mesh : model_meshes)
    {
        mesh->SetMaterial(m);
    }
}

MeshGroup::~MeshGroup()
{
    glDeleteVertexArrays(1, &VAO);
    for (auto mesh : model_meshes)
    {
        delete mesh;
        mesh = nullptr;
    }
    std::cout << "ModelMesh <" << name << "> Destructor Called" << std::endl;
}
