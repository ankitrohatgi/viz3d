#include "glutils.h"
#include <iostream>

namespace viz3d {

void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW error: " << error << ": " << description << std::endl;     
}

}
