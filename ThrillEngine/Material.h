#pragma once
#include <glad/glad.h>

#include <string>
#include "Shader.h"

// Material class will be used in objectmanager when drawing.
// In draw part,  Use(id) -> draw function from object class-> UnUse()
class Material
{
public:
    ~Material();

    void Use();
    void UnUse();
    void SetProgramHandle(const std::string& input_program);
    GLuint GetProgramHandle();
    void SetColor(glm::vec4 input);
    
    Shader shader;
    glm::vec4 color = glm::vec4(1.0f);
private:


   
};
