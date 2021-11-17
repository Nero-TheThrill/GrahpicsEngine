#include "SkyBox.h"

#include "Graphics.h"

SkyBox::SkyBox(std::string n)
{
    id = 0;
    name = n;
    draw_normal_shader = GRAPHICS->GetShader("test");
    mesh = nullptr;
}

SkyBox::~SkyBox()
{
}

void SkyBox::SetMeshGroup(MeshGroup* input)
{
    mesh = input;
}

void SkyBox::Update()
{
    mesh->mapping_mode = mapping_mode;
    mesh->should_calculate_uv_in_gpu = should_calculate_uv_in_gpu;
    mesh->mapping_with_normal = mapping_with_normal;
    Draw();
}

void SkyBox::SetShader(std::string id)
{
    shader = GRAPHICS->GetShader(id);
}

void SkyBox::Draw()
{
    if (mesh != nullptr)
    {
        mesh->mapping_mode = mapping_mode;
        mesh->should_calculate_uv_in_gpu = should_calculate_uv_in_gpu;
        mesh->ChangeMode(drawmode);
        glUseProgram(shader.program_handle);
        shader.set("item_selected", item_selected);
        if (material != nullptr)
            mesh->SetMaterial(material);
   

        mesh->Draw(shader);
        glUseProgram(0);
    }
}

void SkyBox::SetTextures()
{
    top = GRAPHICS->GetTexture("skybox_top");
    bottom = GRAPHICS->GetTexture("skybox_bottom");
    left = GRAPHICS->GetTexture("skybox_left");
    right = GRAPHICS->GetTexture("skybox_right");
    front = GRAPHICS->GetTexture("skybox_front");
    back = GRAPHICS->GetTexture("skybox_back");
}
