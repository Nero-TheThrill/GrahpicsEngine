#include "LevelManager.h"

#include <iostream>
#include "imGUIManager.h"
#include "Object.h"

LevelManager* LEVELMANAGER = nullptr;
LevelManager::LevelManager()
{
    LEVELMANAGER = this;
    current_level = nullptr;
}

void LevelManager::Init()
{
    std::cout << "LevelManager Initialize" << std::endl;
}

void LevelManager::Update()
{
    if (current_level != nullptr)
        current_level->Update();
}

void LevelManager::ChangeLevel(LevelID levelid)
{
    //if (current_level != nullptr)
    //{
    //    delete current_level;
    //    current_level = nullptr;
    //}

    current_level = levels[levelid];
    current_level->Init();
    IMGUIMANAGER->current_item = nullptr;
}

void LevelManager::InsertLevel(LevelStructure* pLevel, LevelID levelid)
{
    levels.insert(std::pair<LevelID, LevelStructure*>(levelid, pLevel));
}



LevelManager::~LevelManager()
{
}
