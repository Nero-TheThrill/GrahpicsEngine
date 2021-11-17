#include "ObjectManager.h"
#include <iostream>

#include "Graphics.h"

ObjectManager* OBJECTMANAGER = nullptr;

ObjectManager::ObjectManager()
{
    OBJECTMANAGER = this;
    genObjectsNum = 0;
    std::cout << "Object Manager Constructor Called" << std::endl;
    //TODO: Initialize framebufferobject
}

void ObjectManager::Init()
{
    skybox = new SkyBox("skybox");
    skybox->SetShader("nolight");
    skybox->SetMeshGroup(GRAPHICS->GetMeshGroup("cube"));
    skybox->SetTextures();
}

void ObjectManager::Update()
{
    if (skybox != nullptr)
    {
        glDepthMask(GL_FALSE);
        skybox->Update();
        glDepthMask(GL_TRUE);
    }
    for (std::unordered_map<unsigned, LightObject*>::iterator light = lightobjects.begin(); light != lightobjects.end(); light++)
    {
        if (!light->second->alive)
        {
            light_to_be_erased.push_back(light->first);
        }
    }
    for (auto light : light_to_be_erased)
    {
        lightobjects.erase(light);
    }

    for (std::unordered_map<unsigned, Object*>::iterator obj = objects.begin(); obj != objects.end(); obj++)
    {
        if (obj->second->alive)
        {
            obj->second->Update();
        }
        else
        {
            need_to_be_erased.push_back(obj->first);
        }
    }
    for (auto obj : need_to_be_erased)
    {
        Object* deletethis = objects.find(obj)->second;
        objects.erase(obj);
        delete deletethis;
    }
    need_to_be_erased.clear();
    light_to_be_erased.clear();
}

void ObjectManager::RegisterObject(Object* obj)
{
   
    genObjectsNum += 1;
    objects.insert(std::make_pair(genObjectsNum, obj));
    obj->id = genObjectsNum;
}

void ObjectManager::RegisterLight(LightObject* light)
{
    lightobjects.insert(std::make_pair(light->id, light));
}

void ObjectManager::DeleteAll()
{
    for (std::unordered_map<unsigned, Object*>::iterator obj = objects.begin(); obj != objects.end(); obj++)
    {
        need_to_be_erased.push_back(obj->first);
    }
    for (std::unordered_map<unsigned, LightObject*>::iterator light = lightobjects.begin(); light != lightobjects.end(); light++)
    {
        light_to_be_erased.push_back(light->first);
    }
    delete skybox;
    skybox = nullptr;
}

Object* ObjectManager::GetObject(std::string id)
{
    Object* result = nullptr;
    for (std::unordered_map<unsigned, Object*>::iterator obj = objects.begin(); obj != objects.end(); obj++)
    {
        if(obj->second->name==id)
        {
            result = obj->second;
        }
    }
    return result;
}

std::unordered_map<unsigned, Object*> ObjectManager::GetAllObjects()
{
    return  objects;
}

std::unordered_map<unsigned, LightObject*> ObjectManager::GetAllLights()
{
    return lightobjects;
}


ObjectManager::~ObjectManager()
{
    for (auto obj : objects)
    {
        delete obj.second;
    }
    delete skybox;
    skybox = nullptr;
    std::cout << "ObjectManager Destructor Called" << std::endl;
}

