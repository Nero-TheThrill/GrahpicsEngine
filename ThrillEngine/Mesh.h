#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Component.h"

class Mesh : public Component
{
public:
    Mesh();
    void Init();
    void Bind();
    void Draw();
    void UnBind();
    ~Mesh();

    std::vector<GLfloat> positions;
    std::vector<GLfloat> texcoords;
    std::vector<GLfloat> normals;

    std::vector<GLint> position_indices;
    std::vector<GLint> texcoord_indices;
    std::vector<GLint> normal_indices;

private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    int index_size;

   
};

