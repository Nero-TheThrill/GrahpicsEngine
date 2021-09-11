#include "ObjectManager.h"
#include <iostream>

ObjectManager* OBJECTMANAGER = nullptr;

ObjectManager::ObjectManager()
{
    OBJECTMANAGER = this;
    genObjectsNum = 0;
}

void ObjectManager::Init()
{
 
}

void ObjectManager::Update()
{
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
        std::cout << "delete" << std::endl;
    }
    need_to_be_erased.clear();
}

void ObjectManager::RegisterObject(Object* obj)
{
   // std::cout<<genObjectsNum<<std::endl;
    genObjectsNum+=1;
    objects[genObjectsNum] = obj;
    obj->id = genObjectsNum;
}

void ObjectManager::DeleteAll()
{
    for (std::unordered_map<unsigned, Object*>::iterator obj = objects.begin(); obj != objects.end(); obj++)
    {
        need_to_be_erased.push_back(obj->first);
    }
}

std::unordered_map<unsigned, Object*> ObjectManager::GetAllObjects()
{
    return  objects;
}


ObjectManager::~ObjectManager()
{
}

