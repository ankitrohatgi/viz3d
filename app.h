#pragma once
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "ui.h"
#include "renderer.h"

namespace viz3d {

class App {
private:
    static constexpr size_t WindowHeight = 600;
    static constexpr size_t WindowWidth = 800;
    
    GLFWwindow *window_ = nullptr;

    viz3d::UIState uiState_;
    viz3d::Renderer renderer_;

    void setupWindow();
    void setupUI();
    static void HandleMouseButton(GLFWwindow* window, int button, int action, int mods);
    static void HandleCursorPos(GLFWwindow* window, double xpos, double ypos);
public:
    App(); // TODO: parse command line params?
    ~App();
    // run event loop etc.
    void run();
};

}
