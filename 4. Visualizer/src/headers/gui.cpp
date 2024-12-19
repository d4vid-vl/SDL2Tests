#include "gui.hpp"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

void GUI_Init(SDL_Window* window, SDL_Renderer* renderer) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

void GUI_Close() {
    ImGui_ImplSDL2_Shutdown();
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui::DestroyContext();
}

void GUI_Renderer(float my_color[4]) {

    static int select = -1;
    const char* figures[] = { "Cube", "Pyramid", "Test1", "Test2" };

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Figure Visualizer");
    ImGui::Text("Select a Figure: ");

    if (ImGui::Button("Select...")) ImGui::OpenPopup("Figure");
    ImGui::SameLine();
    ImGui::TextUnformatted(select == -1 ? "<None>" : figures[select]);

    if (ImGui::BeginPopup("Figure")) {

        ImGui::SeparatorText("Figures!");
        for (int i = 0; i < IM_ARRAYSIZE(figures); i++) 
            if(ImGui::Selectable(figures[i])) 
                select = i;
        ImGui::EndPopup();  
    };

    ImGui::Text("Change the color outline: ");
    ImGui::ColorEdit4("Color", my_color);

    ImGui::End();
    ImGui::Render();    
}
