#include "Engine.h"
#include "Application.h"
#include "LevelManager.h"
#include "TestLevel.h"

int main()
{
    
    auto* ThrillEngine = new Engine();
    ThrillEngine->Init();
    LevelStructure* testlevel = new TestLevel();
    LEVELMANAGER->InsertLevel(testlevel,1);
    LEVELMANAGER->ChangeLevel(1);
    ThrillEngine->Loop();
    ThrillEngine->Quit();
    delete ThrillEngine;
    return 0;
}

