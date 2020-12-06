#pragma once

#include <GL/gl3w.h>

#include <vector>

namespace viz3d {
    class Renderer {
    private:
        std::vector<float> cloudVertices_;
        GLuint vao1_;
        GLuint vao2_;
        GLint colorUniformLoc_;

    public:
        void init();
        void render();

        // handle mouse inputs
        // add point cloud/object etc.
        // change projection
        // show/hide things? - maybe need an asset manager?
    };
}