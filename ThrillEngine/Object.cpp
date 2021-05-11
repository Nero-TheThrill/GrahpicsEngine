#include "Object.h"
#include "Input.h"
#include "Material.h"
#include "ObjectManager.h"




void Object::Update()
{
    draw();
}

Object::Object()
{
    id = 0;
    mesh.Init();
    transform.Init();
    OBJECTMANAGER->RegisterObject(this);
}



Object::~Object()
{
}


void Object::SetColor(glm::vec4 color)
{
    material.SetColor(color);
}

void Object::draw()
{
    material.Use();
    material.shader.set("model", transform.GetTransformMatrix());
    material.SetColor(glm::vec4(1.0));
    texture.Update();
    mesh.Draw();
    material.UnUse();
}



//should change pick_shader -> pick_material and should make materials in outside of engine.lib
void Object::pick_shader(const std::string& name)
{
    material.SetProgramHandle(name);
}

