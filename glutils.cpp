#include "glutils.h"
#include <iostream>

namespace viz3d {

namespace {

GLuint CompileShader(GLenum shaderType, const char* shaderText) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderText, nullptr);
    glCompileShader(shader);
    int success;
    char info[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::cerr << "error: " << info << std::endl;
        exit(1);
    }
    return shader;
}

}

void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW error: " << error << ": " << description << std::endl;     
}

GLuint LoadShaders(const char* vertexShaderText, const char* fragmentShaderText) {
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderText);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderText);

    // program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int success;
    char info[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, info);
        std::cerr << "error: " << info << std::endl;
        exit(1);
    }

    // glUseProgram(shaderProgram);
    return shaderProgram;
}

}
