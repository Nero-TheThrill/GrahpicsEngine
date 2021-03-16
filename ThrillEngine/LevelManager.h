#pragma once
#include <unordered_map>
#include "EngineCore.h"
#include "LevelStructure.h"

using LevelID = unsigned;

class LevelManager :public EngineCore
{
public:
    LevelManager();
    void Init() override;
    void Update() override;
    void ChangeLevel(LevelID levelid);
    void InsertLevel(LevelStructure* pLevel, LevelID levelid);
    ~LevelManager();
private:
    std::unordered_map<LevelID ,LevelStructure*> levels;
    LevelStructure* current_level;
};
extern LevelManager* LEVELMANAGER;