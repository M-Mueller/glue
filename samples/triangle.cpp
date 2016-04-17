#include <glue/GlBuffer.h>
#include <glue/GlProgram.h>
#include <glue/GlVertexArray.h>
#include <glue/GlVertexBuffer.h>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdio>
#include <thread>

#include "common.h"

#define GLSL(src) "#version 330\n" #src

int main()
{
    auto window = createWindow(800, 600);
    if(!window)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::string vertexShader = GLSL(
        in vec2 position;
        in vec3 color;

        out vec3 fs_color;

        void main()
        {
            fs_color = color;
            gl_Position = vec4(position, 0.0, 1.0);
        }
    );

    std::string fragmentShader = GLSL(
        in vec3 fs_color;
        out vec4 out_color;

        void main()
        {
            out_color = vec4(fs_color, 1.0);
        }
    );
    auto program = make_unique<GlProgram>(vertexShader, fragmentShader);

    std::vector<glm::vec2> vertices = {
        glm::vec2(0.0f,  0.5f),
        glm::vec2(0.5f, -0.5f),
        glm::vec2(-0.5f, -0.5f)
    };
    std::vector<glm::vec3> colors = {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    };

    auto vbo = make_unique<GlVertexBuffer>();
    vbo->bind();
    vbo->setData(GlBuffer::Usage::StaticDraw, vertices, colors);

    auto vao = make_unique<GlVertexArray>();
    vao->bind();
    vao->setVertexData(*vbo);
    vao->release();

    vbo->release();

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        program->activate();
        vao->bind();
        vao->draw(GlVertexArray::Primitive::Triangles);
        vao->release();
        program->deactivate();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

