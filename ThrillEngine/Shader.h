#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:
    void set(const std::string& value_name, glm::vec4 color) const;
    void set(const std::string& value_name, glm::vec3 color) const;
    void set(const std::string& value_name, bool value) const;
    void set(const std::string& value_name, int value) const;
    void set(const std::string& value_name, float value) const;
    void set(const std::string& value_name, glm::mat4 matrix) const;

    GLuint program_handle = 0;
    std::string name;

private:


};
