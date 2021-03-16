#include "TestLevel.h"

#include <iostream>


#include "Input.h"
#include "ObjectManager.h"

TestLevel::TestLevel()
{
}

void TestLevel::Init()
{
    obj = new Object();
    obj->SetObject("null", "box");
    OBJECTMANAGER->RegisterObject(obj);

}

void TestLevel::Update()
{
    if (Input::IsTriggered(GLFW_KEY_1))
    {
        obj = new Object();
        obj->SetObject("null", "box");
        OBJECTMANAGER->RegisterObject(obj);
    }
    if (Input::IsTriggered(GLFW_KEY_2)&&obj!=nullptr)
    {
        OBJECTMANAGER->DeleteAll();
    }

}

void TestLevel::Close()
{
}

TestLevel::~TestLevel()
{
}
