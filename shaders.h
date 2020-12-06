#pragma once

namespace viz3d {

const char* DEFAULT_VERTEX_SHADER = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main() { gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); }
    )";

const char* DEFAULT_FRAGMENT_SHADER = R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec4 uColor;
    void main() {
        FragColor = uColor;
    }
    )";

}