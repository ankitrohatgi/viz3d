#pragma once

namespace viz3d {

// store UI state here, or is this just application state??
// should this just come from some data model of the app??
struct UIState {
    bool showAbout_ = false;
    bool showImGuiDemo_ = false;
};

void RenderUI(UIState *uiState);

}
