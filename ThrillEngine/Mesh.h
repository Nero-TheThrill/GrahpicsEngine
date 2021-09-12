#pragma once
#include <string>
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Component.h"

enum DrawType
{
    DRAWELEMENT,
    DRAWARRAY
};

enum DrawMode
{
    TRIANGLES,
    LINES,
    TRIANGLSTRIP
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

    std::vector<GLfloat> positions_use_indices;
    std::vector<GLfloat> texcoords;
    std::vector<GLfloat> normals;

    std::vector<GLint> position_indices;
    std::vector<GLint> texcoord_indices;
    std::vector<GLint> normal_indices;

    std::vector<GLfloat> positions;
    int face_stride=0;
    std::string name;
private:
    GLuint VAO;
    GLuint VBO_positions, VBO_normals;
    GLuint EBO;
    int index_size;


};

