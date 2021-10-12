#include "ObjectManager.h"
#include <iostream>

ObjectManager* OBJECTMANAGER = nullptr;

ObjectManager::ObjectManager()
{
    OBJECTMANAGER = this;
    genObjectsNum = 0;
    std::cout << "Object Manager Constructor Called" << std::endl;
}

void ObjectManager::Init()
{

}

void ObjectManager::Update()
{
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
    std::cout << "ObjectManager Destructor Called" << std::endl;
}

