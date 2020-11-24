#pragma once
#include <GL/gl3w.h>

namespace viz3d {

void glfw_error_callback(int error, const char* description);

GLuint LoadShaders(const char* vertexShaderText, const char* fragmentShaderText);

}
