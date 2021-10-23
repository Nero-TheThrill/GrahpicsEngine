#pragma once
#include"glm/glm.hpp"
glm::vec2 GenerateSphericalUV(glm::vec3 vec);
glm::vec2 GenerateCylindricalUV(glm::vec3 vec, float max_y, float min_y);
glm::vec2 GeneratePlanarUV(glm::vec3 vec);

