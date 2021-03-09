#include "Engine.h"

#include "Application.h"
#include "Graphics.h"
#include "Input.h"


Engine* ThrillEngine = nullptr;

Engine::Engine()
{
    isgamerunning = true;
    ThrillEngine = this;
}

Engine::~Engine()
{
    ThrillEngine = nullptr;
}

void Engine::Init()
{
    Input::Init();
    AddCore(new Graphics());
    AddCore(new Application());
    for (auto* e_core : enginecore)
        e_core->Init();
    APPLICATION->AppSet(1380, 720);
    GRAPHICS->DrawTriangle();
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
