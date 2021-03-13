#include "ObjectManager.h"
#include <iostream>
#include "Input.h"

ObjectManager* OBJECTMANAGER = nullptr;
std::vector<Object*> newobj;
std::vector<Object*> newobj1;
void ObjectManager::Init()
{
    //move these codes to the level class later.
    genObjectsNum = 0;
}

void ObjectManager::Update()
{
    if (Input::IsTriggered(GLFW_KEY_1))
    {
        Object* obj = new Object();
        newobj.push_back(obj);
        obj->SetObject("null", "box");
        RegisterObject(obj);
    }
    if (Input::IsTriggered(GLFW_KEY_2))
    {
        Object* obj = new Object();
        newobj1.push_back(obj);
        obj->SetObject("null", "box1");
        RegisterObject(obj);
    }
    if(Input::IsTriggered(GLFW_KEY_3))
    {
        for(auto obj : newobj)
         obj->alive = false;
    }
    if (Input::IsTriggered(GLFW_KEY_4))
    {
        for (auto obj : newobj1)
            obj->alive = false;
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
        std::cout << "delete" << std::endl;
    }
    need_to_be_erased.clear();
}

void ObjectManager::RegisterObject(Object* obj)
{
    std::cout<<genObjectsNum<<std::endl;
    genObjectsNum+=1;
    objects[genObjectsNum] = obj;
    obj->id = genObjectsNum;
}


ObjectManager::~ObjectManager()
{
}

