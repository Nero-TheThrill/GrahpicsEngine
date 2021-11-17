#pragma once
#include <string>

#include "MeshGroup.h"

class SkyBox
{
public:
    SkyBox(std::string n);
    ~SkyBox();
    void SetMeshGroup(MeshGroup* input);
    void Update();
    void SetShader(std::string id);
    void Draw();
    void SetTextures();
    bool alive = true;
    unsigned id;
    int drawmode = 0;// 0: facenormal 1: vertexnormal
    bool shouldDrawNormals = false;
    MeshGroup* mesh;
    Shader shader, draw_normal_shader;
    std::string name;
    bool item_selected = false;
    int mapping_mode = 0; // 0: default, 1: spherical, 2: cylindrical, 3: planar
    bool should_calculate_uv_in_gpu = true;
    bool mapping_with_normal = false;
    int top, bottom, front, back, left, right;//texture
};

