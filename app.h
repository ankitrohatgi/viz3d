#pragma once
#include <GLFW/glfw3.h>

namespace viz3d {

class App {
private:
    static constexpr size_t WindowHeight = 600;
    static constexpr size_t WindowWidth = 800;
    
    GLFWwindow *window_ = nullptr;
    bool showDemoWindow_ = true;

    void setupWindow();
    void setupUI();
    void setupGL();

public:
    App();
    ~App();
    // run event loop etc.
    void run();
};

}
