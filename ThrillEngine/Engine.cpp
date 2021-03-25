#include "Engine.h"

#include "Application.h"
#include "Graphics.h"
#include "Input.h"
#include "ObjectManager.h"
#include "LevelManager.h"
Engine::Engine()
{
    isgamerunning = true;
}

Engine::~Engine()
{
}

void Engine::Init()
{
    Input::Init();
    AddCore(new Application());
    AddCore(new Graphics());
    AddCore(new ObjectManager());
    AddCore(new LevelManager());
    for (auto* e_core : enginecore)
        e_core->Init();
    APPLICATION->AppSet(800, 600);
   // GRAPHICS->DrawTriangle();
}

void Engine::Loop()
{
    while (APPLICATION->shouldClose()&&isgamerunning)
    {
        Input::Update();
        for (auto* e_core : enginecore)
            e_core->Update();
    }
}

void Engine::Quit()
{
    isgamerunning = false;
    for(auto* e_core : enginecore)
    {
        delete e_core;
        e_core = nullptr;
    }
}

void Engine::AddCore(EngineCore* input_core)
{
    enginecore.push_back(input_core);
}
