#pragma once
#include <vector>
#include "EngineCore.h"
#include "Object.h"
#include <unordered_map>

#include "Camera.h"


class Graphics : public EngineCore
{
public:

    void Init() override;
    void Update() override;
    ~Graphics() override;
    void InitVPmatrices();
    void UpdateVPmatrices();
    void CompileShader(const std::string& vertexshader_id, const std::string& fragmentshader_id, const std::string& program_id);
    void LoadVertexShader(const std::string& path, const std::string& id);
    void LoadFragmentShader(const std::string& path, const std::string& id);
    GLuint GetProgramHandle(const std::string& program_id);
private:

    std::unordered_map<std::string /*id*/, std::string /*shader*/> fragment_shaders;
    std::unordered_map<std::string /*id*/, std::string /*shader*/> vertex_shaders;
    std::string log_string; // log for OpenGL compiler and linker messages
    std::unordered_map < std::string /*id*/, GLuint/*program handle*/> program_handles;
    Camera camera;
    unsigned int uboMatrices;

};
extern Graphics* GRAPHICS;
