#include "imGUIManager.h"
#include <iostream>
#include "Graphics.h"
#include "ObjectManager.h"
imGUIManager* IMGUIMANAGER = nullptr;

imGUIManager::imGUIManager(GLFWwindow* window)
{
    IMGUIMANAGER=this;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsLight();

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

        
        
        std::unordered_map<unsigned, Object*> objects = OBJECTMANAGER->GetAllObjects();
        
        if (ImGui::BeginCombo("select object", current_item!=nullptr?current_item->name.c_str():""))
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
        if(current_item!=nullptr)
        {
            glm::vec3 pos=current_item->transform.position;
            ImGui::SliderFloat3("translation", glm::value_ptr(pos), -10, 10);
            current_item->transform.Translate(pos);


            std::unordered_map<std::string , Material*> materials = GRAPHICS->GetAllMaterial();
            std::string current_material = current_item->material->name;

            if (ImGui::BeginCombo("select_material", current_material.c_str()))
            {
                for (auto mat : materials)
                {
                    bool is_selected = (current_material == mat.second->name);
                    if (ImGui::Selectable(mat.second->name.c_str(), is_selected))
                    {
                        current_material = mat.second->name;
                        current_item->pick_material(mat.second->name);
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
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
