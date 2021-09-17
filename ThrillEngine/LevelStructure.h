#pragma once
#include <iostream>

class LevelStructure
{
public:

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Close() = 0;
    virtual ~LevelStructure()
    {
    }

};
