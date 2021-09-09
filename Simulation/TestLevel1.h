#pragma once
#include "LevelStructure.h"
#include "Object.h"
class TestLevel1 : public LevelStructure
{
public:
    TestLevel1();
    void Init() override;
    void Update() override;
    void Close() override;
    ~TestLevel1();
private:
    Object* obj1, * obj2, * obj3;

};

