#include "LevelManager.h"

LevelManager* LEVELMANAGER = nullptr;
LevelManager::LevelManager()
{
    LEVELMANAGER = this;
    current_level = nullptr;
}

void LevelManager::Init()
{
}

void LevelManager::Update()
{
    if(current_level!=nullptr)
        current_level->Update();
}

void LevelManager::ChangeLevel(LevelID levelid)
{
    if (current_level != nullptr)
    {
        delete current_level;
        current_level = nullptr;
    }

    current_level = levels[levelid];
    current_level->Init();
}

void LevelManager::InsertLevel(LevelStructure* pLevel, LevelID levelid)
{
    levels.insert(std::pair<LevelID, LevelStructure*>(levelid, pLevel));
}



LevelManager::~LevelManager()
{
}
