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
    Material(const std::string& id);
    ~Material();

    void Use();
    void UnUse();
    void Update();
    void PickShader(const std::string& input_program);
    void set(const std::string& value_id, glm::vec3 input);
    void set(const std::string& value_id, glm::vec4 input);
    void set(const std::string& value_id, float input);
    void set(const std::string& value_id, bool input);
    void set(const std::string& value_id, int input);
    void set(const std::string& value_id, glm::mat4 input);



    GLuint GetProgramHandle();

    Texture texture;
    Shader shader;
    std::string name;
private:
    std::unordered_map<std::string, glm::vec3> set_values_v3;
    std::unordered_map<std::string, glm::vec4> set_values_v4;
    std::unordered_map<std::string, glm::mat4> set_values_m4;
    std::unordered_map<std::string, float> set_values_float;
    std::unordered_map<std::string, int> set_values_int;
    std::unordered_map<std::string, bool> set_values_bool;
};

