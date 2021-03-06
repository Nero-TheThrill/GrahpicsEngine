#include "Object.h"

#include "Graphics.h"
#include "Input.h"
#include "Material.h"
#include "ObjectManager.h"




void Object::Update()
{

    Draw();
}

void Object::SetShader(std::string id)
{
    shader = GRAPHICS->GetShader(id);
}

Object::Object(std::string n)
{
    id = 0;
    transform.Init();
    OBJECTMANAGER->RegisterObject(this);
    name = n;
    draw_normal_shader = GRAPHICS->GetShader("test");
    mesh = nullptr;
    material = nullptr;
    alive = true;
}

Object::Object(std::string n, Object* obj)
{
    id = 0;
    transform.Init();
    OBJECTMANAGER->RegisterObject(this);
    name = n;
    color = obj->color;
    transform = obj->transform;
    mesh = obj->mesh;
    drawmode = obj->drawmode;
    shouldDrawNormals = obj->shouldDrawNormals;
    draw_normal_shader = obj->draw_normal_shader;
    shader = obj->shader;
    material = obj->material;
    alive = true;
}


Object::~Object()
{
}


void Object::SetColor(glm::vec3 inputcolor)
{
    color = inputcolor;
}

void Object::SetMeshGroup(MeshGroup* input)
{
    mesh = input;
}

void Object::Draw()
{
    if (mesh != nullptr)
    {
        mesh->mapping_mode = mapping_mode;
        mesh->should_calculate_uv_in_gpu = should_calculate_uv_in_gpu;
        mesh->mapping_with_normal = mapping_with_normal;

           
        mesh->ChangeMode(drawmode);
        glUseProgram(shader.program_handle);
        shader.set("model", transform.GetTransformMatrix());
        shader.set("objectColor", color);
        shader.set("item_selected", item_selected);
        shader.set("isModePhongShading_EnvironmentMapping", isModePhongShading_EnvironmentMapping);
        shader.set("environmentmapping_mode", environmentmapping_mode);
        shader.set("R", R);
        shader.set("G", G);
        shader.set("B", B);
        shader.set("RatioDenominator", RatioDenominator);
        shader.set("mixRate", mixRate);
        mesh->Draw(shader, material);
        glUseProgram(0);
        if (shouldDrawNormals)
        {
            glUseProgram(draw_normal_shader.program_handle);
            draw_normal_shader.set("model", transform.GetTransformMatrix());
            draw_normal_shader.set("objectColor", glm::vec3(1));
            mesh->DrawNormals();
            glUseProgram(0);
        }
    }
}

void Object::SendView(glm::vec3 v)
{
    glUseProgram(shader.program_handle);
    shader.set("test", v);
    glUseProgram(0);
}




