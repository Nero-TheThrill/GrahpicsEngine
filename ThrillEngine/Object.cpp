#include "Object.h"
#include "Input.h"
#include "Material.h"
#include <iostream>

#include "ObjectManager.h"
#include "stb_image.h"



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
    material.set("model", transform.GetTransformMatrix());
    material.SetColor(material.color);
    texture.Update();
    mesh.Draw();
    material.UnUse();
}

void Object::pick_shader(const std::string& name)
{
    material.SetProgramHandle(name);
}

