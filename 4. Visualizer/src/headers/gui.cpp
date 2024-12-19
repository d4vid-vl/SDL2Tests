#include "gui.hpp"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer2.h>

int select = -1;
const char* figures[] = { "Cube", "Pyramid" };

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

int GUI_Renderer(float my_color[4], float my_rads[3], int* length, int position[2]) {

    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;
    window_flags |= ImGuiWindowFlags_NoResize;
    window_flags |= ImGuiWindowFlags_NoMove;

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(350, 250), ImGuiCond_FirstUseEver);

    ImGui::Begin("Figure Visualizer", nullptr, window_flags);
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

    ImGui::Text("Rotation (rad): ");
    ImGui::DragFloat3("Rads", my_rads, 0.00001, -0.005, 0.005, "%.5f");
    ImGui::Text("Length: ");
    ImGui::SliderInt("Length", length, 20, 400);
    ImGui::Text("Position:");
    ImGui::SliderInt2("Position", position, 0, 700);

    ImGui::End();
    ImGui::Render();

    return select;
}
