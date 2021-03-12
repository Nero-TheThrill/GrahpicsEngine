#pragma once
#include <glad/glad.h>

#include <string>
#include <unordered_map>

#include "EngineCore.h"

// Material class will be used in objectmanager when drawing.
// In draw part,  Use(id) -> draw function from object class-> UnUse()
class Material : public EngineCore
{
public:
    void Init() override;
    void Update() override;
    ~Material() override;
    void LoadVertexShader(const std::string& path, const std::string& id);
    void LoadFragmentShader(const std::string& path, const std::string& id);
    void CompileShader(const std::string& vertexshader_id, const std::string& fragmentshader_id, const std::string& program_id);
    void Use(const std::string& program_id);
    void UnUse();
    
private:
    std::unordered_map<std::string /*id*/, std::string /*shader*/> fragment_shaders;
    std::unordered_map<std::string /*id*/, std::string /*shader*/> vertex_shaders;
    std::string log_string; // log for OpenGL compiler and linker messages
    std::unordered_map < std::string /*id*/, GLuint/*program handle*/> program_handles;
};
extern Material* MATERIALS;
