#pragma once
#include "Object.h"

enum class LightType
{
    POINT,
    DIRECTIONAL,
    SPOT
};
class LightObject : public Object
{
public:
    LightObject(std::string n);
    LightType type = LightType::POINT;
};

