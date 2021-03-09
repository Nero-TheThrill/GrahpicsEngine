#include "Engine.h"
#include "Application.h"
int main()
{
    auto* ThrillEngine = new Engine();
    ThrillEngine->Init();
    ThrillEngine->Loop();
    ThrillEngine->Quit();
    delete ThrillEngine;
    return 0;
}

