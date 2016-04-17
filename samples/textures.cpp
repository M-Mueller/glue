#include <glue/GlBuffer.h>
#include <glue/GlProgram.h>
#include <glue/GlVertexArray.h>
#include <glue/GlVertexBuffer.h>
#include <glue/GlTexture2D.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
        LOG(ERROR) <<  "Failed to create window";
        glfwTerminate();
        return -1;
    }

    std::string vertexShader = GLSL(
        uniform mat4 projectionMatrix;
        uniform mat4 viewMatrix;
        uniform mat4 modelMatrix;
        in vec3 position;
        in vec2 texCoord;

        out vec2 fs_texCoord;

        void main()
        {
            fs_texCoord = texCoord;
            gl_Position = projectionMatrix*viewMatrix*modelMatrix*vec4(position, 1.0);
        }
    );

    std::string fragmentShader = GLSL(
        uniform sampler2D tex;
        in vec2 fs_texCoord;
        out vec4 out_color;

        void main()
        {
            out_color = texture(tex, fs_texCoord);
        }
    );

    auto program = make_unique<GlProgram>(vertexShader, fragmentShader);

    std::vector<glm::vec3> vertices = {
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, 0.0f),
        glm::vec3(-1.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
    };
    std::vector<glm::vec2> texCoord = {
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
    };

    auto vbo = make_unique<GlVertexBuffer>();
    vbo->bind();
    vbo->setData(GlBuffer::Usage::StaticDraw, vertices, texCoord);

    auto vao = make_unique<GlVertexArray>();
    vao->bind();
    vao->setVertexData(*vbo);
    vao->release();

    vbo->release();

    std::ifstream pinguin("pinguin.png");
    if(!pinguin.is_open())
    {
        LOG(ERROR) << "Could not open Pinguin.png texture";
        return -1;
    }
    auto texture = std::unique_ptr<GlTexture2D>(GlTexture2D::fromPNG(pinguin));
    if(!texture)
    {
        LOG(ERROR) << "Could not load Pinguin.png texture";
        return -2;
    }
    texture->setMinFilter(GlTexture::MinFilter::Linear);
    texture->setMagFilter(GlTexture::MagFilter::Linear);

    auto start = std::chrono::system_clock::now();
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f),
                                                      800.0f/600.0f, 1.0f, 10.0f);
        glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, -3.0f, 3.0f),
                                           glm::vec3(0.0f, 0.0f, 0.0f),
                                           glm::vec3(0.0f, 1.0f, 1.0f));

        auto now = std::chrono::system_clock::now();
        float elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(now - start).count();
        glm::mat4 modelMatrix = glm::rotate(glm::mat4(),
                                            elapsed * glm::radians(90.0f),
                                            glm::vec3(0.0f, 0.0f, 1.0f));

        program->activate();
        program->setUniform("projectionMatrix",projectionMatrix);
        program->setUniform("viewMatrix", viewMatrix);
        program->setUniform("modelMatrix", modelMatrix);

        int textureUnit = 0;
        texture->bind(textureUnit);
        program->setUniform("tex", textureUnit);

        vao->bind();
        vao->draw(GlVertexArray::Primitive::TriangleStrip);
        vao->release();

        texture->release(textureUnit);
        program->deactivate();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

