#pragma once
class EngineCore
{
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual ~EngineCore()
    {

    }
};