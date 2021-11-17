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

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, top);
        shader.set("top", 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, bottom);
        shader.set("bottom", 1);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, left);
        shader.set("left", 2);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, right);
        shader.set("right", 3);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, front);
        shader.set("front", 4);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, back);
        shader.set("back", 5);

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
