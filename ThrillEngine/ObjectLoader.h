#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <sstream>
#include<fstream>
#define GLM_ENABLE_EXPERIMENTAL
#include  "glm/gtx/hash.hpp"
#include "MeshGroup.h"
#include "ModelMesh.h"
class ObjectLoader
{
public:
    void loadObject(const std::string& path, const std::string& mesh);

    void reArrangeData();
    void reSizeObject();



private:
    MeshGroup* meshgroup;
    ModelMesh* mesh;

    std::vector<glm::vec3> tmp_positions;
    std::vector<glm::vec3> tmp_normals;
    std::vector<glm::vec2> tmp_texcoords;

    std::vector<int> tmp_positions_indices;
    std::vector<int> tmp_normal_indices;
    std::vector<int> tmp_texture_indices;

    std::unordered_map<glm::ivec3, int> pos_texcoord_norm_indices;

    int tmp_glInt_p1 = 0, tmp_glInt_p2 = 0, tmp_glInt_p3 = 0;
    int tmp_glInt_n1 = 0, tmp_glInt_n2 = 0, tmp_glInt_n3 = 0;
    int tmp_glInt_t1 = 0, tmp_glInt_t2 = 0, tmp_glInt_t3 = 0;

    double min_val_x = DBL_MAX;
    double max_val_x = DBL_MIN;
    double max_val_y = max_val_x, min_val_y = min_val_x;
    double max_val_z = max_val_x, min_val_z = min_val_x;

    std::stringstream ss;
};

