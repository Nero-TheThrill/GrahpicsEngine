#pragma once
#include "LevelStructure.h"
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
    Object* obj1, * obj2, * obj3, * obj4, * obj5, *orbit ,*graycamostarwars, *camostarwars, *ministarwars1,*ministarwars2, *dinosaur,*camostarwars1;
    Object* c1, * c2, * c3, * c4, * c5, * c6, * c7, * c8;
    Object* skysphere;

};

