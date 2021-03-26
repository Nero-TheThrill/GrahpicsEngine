#pragma once
#include <glad/glad.h>

#include <string>
#include <vector>
#include <glm/glm.hpp>


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
    void set(const std::string& value_name, glm::vec4 color) const;
    void set(const std::string& value_name, bool value) const;
    void set(const std::string& value_name, int value) const;
    void set(const std::string& value_name, float value) const;
    void set(const std::string& value_name, glm::mat4 matrix) const;
    void SetColor(glm::vec4 input);

    glm::vec4 color = glm::vec4(1.0f);
private:
    GLuint program_handle=0;
   
};
