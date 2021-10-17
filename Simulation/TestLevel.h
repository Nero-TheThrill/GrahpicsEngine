#pragma once
#include "LevelStructure.h"
#include "LightObject.h"
#include "Object.h"
class TestLevel : public LevelStructure
{
public:
    TestLevel();
    void Init() override;
    void Update() override;
    void Close() override;
    ~TestLevel();
private:
    Object* obj1, * obj2, * obj3, * obj4, * obj5, *orbit ,* centerobj,*baron,*penguin;
    std::vector<LightObject*> lights;
    Object* skysphere;
    float time_count;
};

