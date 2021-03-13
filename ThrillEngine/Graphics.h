#pragma once
#include <vector>
#include "EngineCore.h"
#include "Object.h"
#include <unordered_map>



class Graphics : public EngineCore
{
public:

    void Init() override;
    void Update() override;
    ~Graphics() override;

    void CompileShader(const std::string& vertexshader_id, const std::string& fragmentshader_id, const std::string& program_id);
    void LoadVertexShader(const std::string& path, const std::string& id);
    void LoadFragmentShader(const std::string& path, const std::string& id);
    GLuint GetProgramHandle(const std::string& program_id);
private:
    std::vector<glm::vec3> position;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normal;
    std::vector<std::vector<int>> face;
    glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f};
    Object obj1,obj2;
    int tmpwhattodraw = 0;


    std::unordered_map<std::string /*id*/, std::string /*shader*/> fragment_shaders;
    std::unordered_map<std::string /*id*/, std::string /*shader*/> vertex_shaders;
    std::string log_string; // log for OpenGL compiler and linker messages
    std::unordered_map < std::string /*id*/, GLuint/*program handle*/> program_handles;


};
extern Graphics* GRAPHICS;
