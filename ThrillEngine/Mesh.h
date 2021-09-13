#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Component.h"




enum class DrawMode
{
    MODEL,
    SPHERE
};
class Mesh : public Component
{
public:
    Mesh();
    void Init();
    void Bind();
    void Draw();
    void UnBind();
    ~Mesh();

    std::vector<float> positions_use_indices;
    std::vector<float> texcoords;
    std::vector<float> normals;

    std::vector<int> position_indices;
    std::vector<int> texcoord_indices;
    std::vector<int> normal_indices;

    std::vector<float> positions;

    std::vector<float> positions_normals_use_indices;;
    int face_stride=0;
    std::string name;

    DrawMode drawmode;
private:
    GLuint VAO;
    GLuint VBO_positions, VBO_normals;
    GLuint EBO;
    int index_size;

};

