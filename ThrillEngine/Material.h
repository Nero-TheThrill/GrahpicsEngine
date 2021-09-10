#pragma once
#include <glad/glad.h>
#include <string>
#include <unordered_map>

#include "Shader.h"
#include "Texture.h"

// Material class will be used in objectmanager when drawing.
// In draw part,  Use(id) -> draw function from object class-> UnUse()
class Material
{
public:
    Material();
    ~Material();

    void Use();
    void UnUse();
    void Update();
    void PickShader(const std::string& input_program);
    void AddValue(const std::string& value_id, glm::vec3 input);
    void AddValue(const std::string& value_id, glm::vec4 input);
    void AddValue(const std::string& value_id, float input);
    void AddValue(const std::string& value_id, bool input);
    void AddValue(const std::string& value_id, int input);
    void AddValue(const std::string& value_id, glm::mat4 input);

    void ChangeValue(const std::string& value_id, glm::vec3 input);
    void ChangeValue(const std::string& value_id, glm::vec4 input);
    void ChangeValue(const std::string& value_id, float input);
    void ChangeValue(const std::string& value_id, bool input);
    void ChangeValue(const std::string& value_id, int input);
    void ChangeValue(const std::string& value_id, glm::mat4 input);

    GLuint GetProgramHandle();

    Texture texture;
    Shader shader;

private:

    glm::vec3 color = glm::vec4(1.0f);
    std::unordered_map<std::string, glm::vec3> set_values_v3;
    std::unordered_map<std::string, glm::vec4> set_values_v4;
    std::unordered_map<std::string, glm::mat4> set_values_m4;
    std::unordered_map<std::string, float> set_values_float;
    std::unordered_map<std::string, int> set_values_int;
    std::unordered_map<std::string, bool> set_values_bool;
};

