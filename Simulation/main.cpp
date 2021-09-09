#include "Engine.h"
#include "Application.h"
#include "Graphics.h"
#include "LevelManager.h"
#include "TestLevel.h"
#include "TestLevel1.h"

int main()
{
    
    auto* ThrillEngine = new Engine();
    ThrillEngine->Init();


    GRAPHICS->LoadShader("../shaders/test.vert", "testvert", VERTEX);
    GRAPHICS->LoadShader("../shaders/test.frag", "testfrag", FRAGMENT);
    GRAPHICS->CompileShader("testvert", "testfrag", "test");

    GRAPHICS->LoadShader("../shaders/texture.vert", "texturevert", VERTEX);
    GRAPHICS->LoadShader("../shaders/texture.frag", "texturefrag", FRAGMENT);
    GRAPHICS->CompileShader("texturevert", "texturefrag", "texture");


    GRAPHICS->LoadTexture("../images/awesomeface.png", "face", RGBA);
    GRAPHICS->LoadTexture("../images/container.jpg", "container", RGB);
    GRAPHICS->LoadTexture("../images/lol.png", "lol", RGB);

    LevelStructure* testlevel = new TestLevel();
    LEVELMANAGER->InsertLevel(testlevel,1);
    LEVELMANAGER->ChangeLevel(1);
    LevelStructure* testlevel1 = new TestLevel1();
    LEVELMANAGER->InsertLevel(testlevel1, 2);

    ThrillEngine->Loop();
    ThrillEngine->Quit();
    delete ThrillEngine;
    return 0;
}

