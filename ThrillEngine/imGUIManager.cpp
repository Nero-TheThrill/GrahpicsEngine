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
    {    ImGui::ShowDemoWindow();
        ImGui::Begin("GraphicsEngine GUI");


        std::unordered_map<unsigned, Object*> objects = OBJECTMANAGER->GetAllObjects();

        if (ImGui::BeginCombo("select object", current_item != nullptr ? current_item->name.c_str() : ""))
        {
            for (auto obj : objects)
            {
                bool is_selected = (current_item == obj.second);
                if (ImGui::Selectable(obj.second->name.c_str(), is_selected))
                {
                    current_item = obj.second;
                }
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
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

            std::unordered_map<std::string, Material*> materials = GRAPHICS->GetAllMaterial();
            std::string current_material = current_item->material->name;

            if (ImGui::BeginCombo("select_material", current_material.c_str()))
            {
                 for (auto mat : materials)
                {
                    bool is_selected = (current_material == mat.second->name);
                    if (ImGui::Selectable(mat.second->name.c_str(), is_selected))
                    {
                        current_material = mat.second->name;
                        current_item->Pick_Material(mat.second->name);
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            std::unordered_map<std::string, Mesh*> meshes = GRAPHICS->GetAllMeshes();
            std::string current_mesh = current_item->mesh->name;
            if (ImGui::BeginCombo("select_mesh", current_mesh.c_str()))
            {
                for (auto mesh : meshes)
                {
                    bool is_selected = (current_mesh == mesh.second->name);
                    if (ImGui::Selectable(mesh.second->name.c_str(), is_selected))
                    {
                        current_mesh = mesh.second->name;
                        current_item->SetMesh(mesh.second);
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
            int e = current_item->mesh->n_mode;
            ImGui::RadioButton("face normal", &e, 0); ImGui::SameLine();
            ImGui::RadioButton("vertex normal", &e, 1);
            current_item->mesh->ChangeMode(e);
         
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
}
