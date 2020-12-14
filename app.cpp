#include "app.h"

#include "glutils.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

namespace viz3d {
App::App() {
    setupWindow();
    setupUI();
    renderer_.init();
}

App::~App() {
}

void App::setupWindow() {
    // create window
    glfwSetErrorCallback(viz3d::glfw_error_callback);
    if (!glfwInit()) {
        std::cerr << "glfw init error!" << std::endl;
        return;
    }

#ifdef __APPLE__
    /* We need to explicitly ask for a 3.2 context on OS X */
        glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    window_ = glfwCreateWindow(WindowWidth, WindowHeight, "learn opengl", nullptr, nullptr);
    if (window_ == nullptr) {
        std::cerr << "error creating window!" << std::endl;
        return;
    }

    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // enable vsync

    bool err = gl3wInit() != 0;
    if (err) {
        std::cerr << "Failed to init OpenGL loader" << std::endl;
        return;
    }

    // attach event handlers
    glfwSetMouseButtonCallback(window_, App::HandleMouseButton);
    glfwSetCursorPosCallback(window_, App::HandleCursorPos);
}

void App::setupUI() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
#ifdef __APPLE__
    ImGui_ImplOpenGL3_Init("#version 150"); // glsl version
#else
    ImGui_ImplOpenGL3_Init("#version 130"); // glsl version
#endif
}

void App::run() {
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();

        // imgui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        viz3d::RenderUI(&uiState_);

        // render imgui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window_, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        // render GL
        renderer_.render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window_);

    }
}

void App::HandleMouseButton(GLFWwindow *window, int button, int action, int mods) {
    // std::cout << "button: " << button << ", action: " << action << std::endl;
}

void App::HandleCursorPos(GLFWwindow *window, double xpos, double ypos) {
    // std::cout << "\tx: " << xpos << ", y: " << ypos << std::endl;
}

}
