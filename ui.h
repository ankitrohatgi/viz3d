#pragma once

namespace viz3d {

// Store UI specific states like window open/close etc.
struct UIState {
    bool showAbout_ = false;
    bool showImGuiDemo_ = false;
};

// may need to pass in a data model etc. at some point
void RenderUI(UIState *uiState);

}
