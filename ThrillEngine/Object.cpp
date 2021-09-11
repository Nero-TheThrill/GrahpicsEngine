#include "Object.h"

#include "Graphics.h"
#include "Input.h"
#include "Material.h"
#include "ObjectManager.h"




void Object::Update()
{
    draw();
}

Object::Object(std::string n)
{
    id = 0;
    mesh.Init();
    transform.Init();
    OBJECTMANAGER->RegisterObject(this);
    name = n;
}



Object::~Object()
{
}


void Object::SetColor(glm::vec3 inputcolor)
{
    color = inputcolor;
}

void Object::draw()
{
    material->Use();
    material->shader.set("model", transform.GetTransformMatrix());
    material->Update();
    material->shader.set("objectColor", color);
    texture.Update();
    mesh.Draw();
    material->UnUse();
}



//should change pick_shader -> pick_material and should make materials outside of engine.lib
void Object::pick_material(const std::string& material_id)
{
    material = GRAPHICS->GetMaterial(material_id);
}

