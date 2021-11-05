#include"UVGenerator.h"

glm::vec2 GenerateSphericalUV(glm::vec3 vec)
{
    float u_s = glm::degrees(atan2(vec.z, vec.x));
    u_s += 180;

    float v_s = 180 - glm::degrees(acos(vec.y / (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z))));
    return glm::vec2(u_s / 360.f, v_s / 180.f);
}

glm::vec2 GenerateCylindricalUV(glm::vec3 vec,float max_y,float min_y)
{
    float u_c = glm::degrees(atan2(vec.z, vec.x));
    u_c += 180;
    
    float v_c = (vec.y -min_y) / (max_y-min_y);

    return glm::vec2(u_c / 360.f, v_c);
}

glm::vec2 GeneratePlanarUV(glm::vec3 vec)
{
    glm::vec3 absVec = abs(vec);
    glm::vec2 planar_uv;
    if (absVec.x >= absVec.y && absVec.x >= absVec.z)
    {
        vec.x < 0 ? planar_uv.x = vec.z / absVec.x : planar_uv.x = -vec.z / absVec.x;
        planar_uv.y = vec.y / absVec.x;
    }
    if (absVec.y >= absVec.x && absVec.y >= absVec.z)
    {
        vec.y < 0 ? planar_uv.x = vec.x / absVec.y : planar_uv.x = -vec.x / absVec.y;
        planar_uv.y = vec.z / absVec.y;
    }
    if (absVec.z >= absVec.y && absVec.z >= absVec.x)
    {
        vec.z < 0 ? planar_uv.x = -vec.x / absVec.z : planar_uv.x = vec.x / absVec.z;
        planar_uv.y = vec.y / absVec.z;
    }
    return  (planar_uv + glm::vec2(1)) * 0.5f;
} 
