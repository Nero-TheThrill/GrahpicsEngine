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
}

Object::Object(std::string n, Object* obj)
{
    transform.Init();
    OBJECTMANAGER->RegisterObject(this);
    name = n;
    color = obj->color;
    transform = obj->transform;
    texture = obj->texture;
    mesh = obj->mesh;
    drawmode = obj->drawmode;
    shouldDrawNormals = obj->shouldDrawNormals;
    draw_normal_shader = obj->draw_normal_shader;
    shader = obj->shader;
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
        mesh->ChangeMode(drawmode);
        glUseProgram(shader.program_handle);
        shader.set("model", transform.GetTransformMatrix());
        shader.set("objectColor", color);
        shader.set("texture_exists", texture.texture != -1);
        shader.set("item_selected", item_selected);
        if (shader.name != "test")
        {
            shader.set("viewPosition", GRAPHICS->camera.cam_position);
            shader.set("lightPosition", GRAPHICS->light->transform.position);
            shader.set("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        }
        texture.Update();
        mesh->Draw();
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



