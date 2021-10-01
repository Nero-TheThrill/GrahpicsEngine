#include "imGUIManager.h"
#include <iostream>
#include "Graphics.h"
#include "ObjectManager.h"
#include "imgui/imgui_impl_opengl3.h"
imGUIManager* IMGUIMANAGER = nullptr;

imGUIManager::imGUIManager(GLFWwindow* window)
{
    IMGUIMANAGER = this;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsClassic();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    std::cout << "imGUI Initialize" << std::endl;
}

void imGUIManager::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    { 
        ImGui::Begin("GraphicsEngine GUI");

        glm::vec3 bgcolor=GRAPHICS->background_color;
        ImGui::DragFloat3("background color", glm::value_ptr(bgcolor), 0.01f, 0, 1);
        GRAPHICS->SetBackgroundColor(glm::vec4(bgcolor, 1.0f));
        std::unordered_map<unsigned, Object*> objects = OBJECTMANAGER->GetAllObjects();

        if (ImGui::BeginCombo("select object", current_item != nullptr ? current_item->name.c_str() : ""))
        {
            for (auto obj : objects)
            {
                if (obj.second != nullptr)
                {
                    bool is_selected = (current_item == obj.second);
                    if (ImGui::Selectable(obj.second->name.c_str(), is_selected))
                    {
                        current_item = obj.second;
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();

                }
            }
            ImGui::EndCombo();
        }
        if (current_item != nullptr)
        {
            glm::vec3 pos = current_item->transform.position;
            ImGui::DragFloat3("translation", glm::value_ptr(pos), 0.1f, -FLT_MAX, FLT_MAX);
            current_item->transform.Translate(pos);

            glm::vec3 scale = current_item->transform.current_scale;
            ImGui::DragFloat3("scale", glm::value_ptr(scale),0.1f, -FLT_MAX, FLT_MAX);
            current_item->transform.Scale(scale);

            glm::vec3 rotate = current_item->transform.current_rotate_axis;
            float degree = current_item->transform.current_rotate_degree;
            ImGui::DragFloat3("rotate axis", glm::value_ptr(rotate), 0.01f, -1,1);
            ImGui::DragFloat("degree", &degree);
            current_item->transform.Rotate(degree, rotate);

            std::unordered_map<std::string, Shader> shaders = GRAPHICS->GetAllShaders();
            std::string current_shader = current_item->shader.name;

            if (ImGui::BeginCombo("select_shader", current_shader.c_str()))
            {
                 for (auto shader : shaders)
                {
                    bool is_selected = (current_shader == shader.second.name);
                    if (ImGui::Selectable(shader.second.name.c_str(), is_selected))
                    {
                        current_shader = shader.second.name;
                        current_item->SetShader(shader.second.name);
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            std::unordered_map<std::string, MeshGroup*> meshes = GRAPHICS->GetAllMeshGroups();
            std::string current_mesh = current_item->mesh->name;
            if (ImGui::BeginCombo("select_mesh", current_mesh.c_str()))
            {
                for (auto mesh : meshes)
                {
                    bool is_selected = (current_mesh == mesh.second->name);
                    if (ImGui::Selectable(mesh.second->name.c_str(), is_selected))
                    {
                        current_mesh = mesh.second->name;
                        current_item->SetMeshGroup(mesh.second);
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            int mode = current_item->drawmode;
            ImGui::RadioButton("face normal", &mode, 0); ImGui::SameLine();
            ImGui::RadioButton("vertex normal", &mode, 1);
            current_item->drawmode = mode;
            bool drawnormal = current_item->shouldDrawNormals;
            ImGui::Checkbox("draw normals", &drawnormal);
            current_item->shouldDrawNormals=drawnormal;
        }

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

imGUIManager::~imGUIManager()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    std::cout << "imGUIManager Destructor Called" << std::endl;
}
