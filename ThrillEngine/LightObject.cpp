#include "LightObject.h"

#include "ObjectManager.h"

LightObject::LightObject(std::string n) :Object(n)
{
    OBJECTMANAGER->RegisterLight(this);
    type=LightType::POINT;
}
