#pragma once
#include <vector>
#include "EngineCore.h"
#include "Object.h"
#include <unordered_map>
#include "stb_image.h"
#include "Camera.h"
#include "Light.h"

enum ShaderType
{
    FRAGMENT,
    VERTEX
};

enum ImageType
{
    RGBA,
    RGB
};

class Graphics : public EngineCore
{
public:

    void Init() override;
    void Update() override;
    ~Graphics() override;
    void InitVPmatrices();
    void UpdateVPmatrices();
    void CompileShader(const std::string& vertexshader_id, const std::string& fragmentshader_id, const std::string& program_id);
    GLuint GetProgramHandle(const std::string& program_id);
    void LoadShader(const std::string& path, const std::string& id, ShaderType type);
    unsigned GetTexture(const std::string& texture_id);
    void AddTexture(const std::string& texture_id, unsigned texture);
    void LoadTexture(const std::string& path, const std::string& texture_id, ImageType image_type);
    Camera camera;
    Light light;
private:

    std::unordered_map<std::string /*id*/, std::string /*shader*/> fragment_shaders;
    std::unordered_map<std::string /*id*/, std::string /*shader*/> vertex_shaders;
    std::string log_string; // log for OpenGL compiler and linker messages
    std::unordered_map < std::string /*id*/, GLuint/*program handle*/> program_handles;
    std::unordered_map<std::string /*id*/, unsigned /*texture*/> textures;

    unsigned int uboMatrices=0, uboLight=0;

};
extern Graphics* GRAPHICS;
