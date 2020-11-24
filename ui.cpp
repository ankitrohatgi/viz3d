#include "ui.h"

#include <imgui.h>

#include <cstdlib>

namespace viz3d {

namespace {

void RenderAboutDialog(bool *open) {
    if(!ImGui::Begin("About viz3d", open, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::End();
        return;
    }

    ImGui::Text("viz3d 0.0 - Simple 3D visualizer");
    ImGui::Separator();
    ImGui::Text("Author: Ankit Rohatgi");
    ImGui::End();
}

void RenderMenuBar(UIState *uiState) {
    if(ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", "CTRL+O")) {
                // open a file
            }
            if (ImGui::MenuItem("Exit", "CTRL+Q")) {
                exit(0);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("About")) {
                // show about dialog
                uiState->showAbout_ = true;
            }
            if (ImGui::MenuItem("Show ImGui Demo")) {
                uiState->showImGuiDemo_ = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

}

void RenderUI(UIState *uiState) {
    RenderMenuBar(uiState);
    if (uiState->showAbout_) RenderAboutDialog(&(uiState->showAbout_)); 
    if (uiState->showImGuiDemo_) ImGui::ShowDemoWindow(&(uiState->showImGuiDemo_));
}

}
