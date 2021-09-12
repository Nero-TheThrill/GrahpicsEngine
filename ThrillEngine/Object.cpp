#include "Object.h"

#include "Graphics.h"
#include "Input.h"
#include "Material.h"
#include "ObjectManager.h"




void Object::Update()
{
    Draw();
}

Object::Object(std::string n)
{
    id = 0;
    transform.Init();
    OBJECTMANAGER->RegisterObject(this);
    name = n;
}

Object::Object(std::string n, Object* obj)
{
    transform.Init();
    OBJECTMANAGER->RegisterObject(this);
    name = n;
    color = obj->color;
    transform = obj->transform;
    texture = obj->texture;
    material = obj->material;
    mesh = obj->mesh;
}


Object::~Object()
{
}


void Object::SetColor(glm::vec3 inputcolor)
{
    color = inputcolor;
}

void Object::SetMesh(Mesh* input)
{
    mesh = input;
}

void Object::Draw()
{
    material->Use();
    material->shader.set("model", transform.GetTransformMatrix());
    material->Update();
    material->shader.set("objectColor", color);
    texture.Update();
    mesh->Draw();
    material->UnUse();
}



//should change pick_shader -> pick_material and should make materials outside of engine.lib
void Object::Pick_Material(const std::string& material_id)
{
    material = GRAPHICS->GetMaterial(material_id);
}

