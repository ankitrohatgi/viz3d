#pragma once

namespace viz3d {

const char* DEFAULT_VERTEX_SHADER = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    uniform mat4 MVP;
    void main() {
        vec4 v = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        gl_Position = MVP*v;
    }
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