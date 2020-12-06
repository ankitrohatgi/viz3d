#include "renderer.h"
#include "glutils.h"
#include "shaders.h"

namespace viz3d {

    void Renderer::init() {
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

        // cloud
        glGenVertexArrays(1, &vao2_);
        glBindVertexArray(vao2_);
        GLuint vbo2;
        glGenBuffers(1, &vbo2);
        glBindBuffer(GL_ARRAY_BUFFER, vbo2);
        glBufferData(GL_ARRAY_BUFFER, cloudVertices_.size()*sizeof(float), cloudVertices_.data(), GL_STATIC_DRAW);

        GLuint shaderProgram = viz3d::LoadShaders(viz3d::DEFAULT_VERTEX_SHADER, viz3d::DEFAULT_FRAGMENT_SHADER);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glUseProgram(shaderProgram);

        colorUniformLoc_ = glGetUniformLocation(shaderProgram, "uColor");
    }

    void Renderer::render() {
        glBindVertexArray(vao1_);
        glUniform4f(colorUniformLoc_, 1.0f, 0.0f, 0.0f, 1.0f);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_LINE_LOOP, 3, 3);
        glBindVertexArray(vao2_);
        glUniform4f(colorUniformLoc_, 1.0f, 1.0f, 0.0f, 1.0f);
        glDrawArrays(GL_POINTS, 0, cloudVertices_.size());
    }

}
