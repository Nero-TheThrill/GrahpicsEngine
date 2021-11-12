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
    Material()=default;
    Material(const std::string& id);
    ~Material();

    void Use();
    void UnUse();
    void Update(Shader shader);
    void set(const std::string& value_id, glm::vec3 input);
    void set(const std::string& value_id, glm::vec4 input);
    void set(const std::string& value_id, float input);
    void set(const std::string& value_id, bool input);
    void set(const std::string& value_id, int input);
    void set(const std::string& value_id, glm::mat4 input);


    Texture texture;
    std::string name;
    glm::vec3 ka = glm::vec3(0.08f), kd = glm::vec3(0.7f), ks = glm::vec3(0.4f);
    glm::vec3 emissive = glm::vec3(0.1f);
    float ns=32;
private:
    std::unordered_map<std::string, glm::vec3> set_values_v3;
    std::unordered_map<std::string, glm::vec4> set_values_v4;
    std::unordered_map<std::string, glm::mat4> set_values_m4;
    std::unordered_map<std::string, float> set_values_float;
    std::unordered_map<std::string, int> set_values_int;
    std::unordered_map<std::string, bool> set_values_bool;
};

