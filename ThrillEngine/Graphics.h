#pragma once
#include <vector>
#include "EngineCore.h"
#include "Object.h"
#include <unordered_map>
#include "stb_image.h"
#include "Camera.h"
#include "MeshGroup.h"

enum class ShaderType
{
    FRAGMENT,
    VERTEX,
    RELOAD_FRAGMENT,
    RELOAD_VERTEX
};


class Graphics : public EngineCore
{
public:
    Graphics();
    void Init() override;
    void Update() override;
    ~Graphics() override;

    void InitPVmatrices();
    void UpdatePVmatrices();

    void InitLightInfo();
    void UpdateLightInfo();

    void CompileShader(const std::string& vertexshader_id, const std::string& fragmentshader_id, const std::string& program_id, bool is_ReCompile=false);
    Shader GetShader(const std::string& id);
    void LoadShader(const std::string& path, const std::string& id, ShaderType type);
    void ReLoadShader();

    void AddTexture(const std::string& texture_id, int texture);
    int GetTexture(const std::string& texture_id);

    void AddMaterial(const std::string& material_id, Material* material);
    Material* GetMaterial(const std::string& material_id);

    void LoadTexture(const std::string& path, const std::string& texture_id);

    MeshGroup* GetMeshGroup(const std::string& mesh_id);
    void AddMeshGroup(const std::string& mesh_id, MeshGroup* mesh_group);

    void AddSphereMesh();

    void SetBackgroundColor(glm::vec4 bgcolor);


    glm::vec4 background_color = glm::vec4(0.61f, 0.61f, 0.9f, 1.0f);
    std::unordered_map<std::string, Material* > GetAllMaterial();
    std::unordered_map<std::string , MeshGroup*> GetAllMeshGroups();
    std::unordered_map < std::string, std::pair<Shader, std::pair<std::string, std::string>>> GetAllShaders();
    Camera camera;
private:
    std::unordered_map<std::string /*id*/, Material* /*material*/> materials;
    std::unordered_map<std::string /*id*/, MeshGroup* /*mesh*/> meshgroups;
    std::unordered_map<std::string /*id*/, std::pair<GLuint /*shader handle*/,std::string/*path*/>> fragment_shaders;
    std::unordered_map<std::string /*id*/, std::pair<GLuint /*shader handle*/, std::string/*path*/>> vertex_shaders;
    std::string log_string; // log for OpenGL compiler and linker messages
    std::unordered_map < std::string /*id*/, std::pair<Shader/*shader*/,std::pair<std::string/*vertex_id*/, std::string/*frag_id*/>>> shaders;
    std::unordered_map<std::string /*id*/, int /*texture*/> textures;

    unsigned int uboMatrices = 0,uboLight=0;

    glm::vec3 fog_color = glm::vec3(0.5, 0.5, 0.5) , global_ambient_color = glm::vec3(0.3, 0.3, 0.8);
    float attenuation=0.5f;

};

inline void Graphics::AddMeshGroup(const std::string& mesh_id, MeshGroup* mesh_group)
{
    meshgroups.insert(std::pair<std::string, MeshGroup*>(mesh_id, mesh_group));
}

extern Graphics* GRAPHICS;
