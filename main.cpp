#include "glutils.h"
#include "ui.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GL/gl3w.h>

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

class App {
private:
    static constexpr size_t WindowHeight = 600;
    static constexpr size_t WindowWidth = 800;

    GLFWwindow *window_ = nullptr;

    // application state
    bool showDemoWindow_ = true;
    viz3d::UIState uiState_;

    std::vector<float> cloudVertices_;
    GLuint vao1_;
    GLuint vao2_;
    GLint colorUniformLoc_;


    void setupWindow() {
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
    }

    void setupImgui() {
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

    void setupGL() {
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
            -0.8f, -0.8f, 0.0f,
            0.8f, -0.8f, 0.0f,
            0.0f, 0.8f, 0.0f
        };

        // fill cloud vertices
        for (float x = -0.5f; x <= 0.5f; x+= +0.01f) {
            for (float y = -0.5f; y <= 0.5f; y+=0.01f) {
                cloudVertices_.push_back(x);
                cloudVertices_.push_back(y);
                cloudVertices_.push_back(0.0f);
            }
        }

        glGenVertexArrays(1, &vao1_);
        glBindVertexArray(vao1_);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  

        // vertex shader
        const char *vertexShaderSource = R"(
                    #version 330 core 
                    layout (location = 0) in vec3 aPos;
                    void main() { gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); })";
        
        // fragment shader
        const char *fragmentShaderSource = R"(
                    #version 330 core
                    out vec4 FragColor;
                    
                    uniform vec4 uColor;

                    void main()
                    {
                        FragColor = uColor;
                    }       
        )";

        // cloud
        glGenVertexArrays(1, &vao2_);
        glBindVertexArray(vao2_);
        GLuint vbo2;
        glGenBuffers(1, &vbo2);
        glBindBuffer(GL_ARRAY_BUFFER, vbo2);
        glBufferData(GL_ARRAY_BUFFER, cloudVertices_.size()*sizeof(float), cloudVertices_.data(), GL_STATIC_DRAW);

        GLuint shaderProgram = viz3d::LoadShaders(vertexShaderSource, fragmentShaderSource);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);  
        glUseProgram(shaderProgram);
        
        colorUniformLoc_ = glGetUniformLocation(shaderProgram, "uColor");

    }

    void renderGL() {
        glBindVertexArray(vao1_);
        glUniform4f(colorUniformLoc_, 1.0f, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_LINE_LOOP, 3, 3);
        glBindVertexArray(vao2_);
        glUniform4f(colorUniformLoc_, 1.0f, 1.0f, 0.0f, 1.0f);
        glDrawArrays(GL_POINTS, 0, cloudVertices_.size());

    }

public:
    App() {
        setupWindow();
        setupImgui();
        setupGL();
    }

   
    void run() {
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
            renderGL();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window_);

        }
    }
};

int main() {
    std::cout << "viz3d" << std::endl;
    App app;
    app.run();
    return 0;
}
