/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/renderer/renderer.h"
#include "protonengine/renderer/shader_program.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image/stb_image.h>

namespace ProtonEngine::Renderer
{

void setWindowContext(ContextLoadFunction func)
{
    gladLoadGLLoader(func);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void renderRenderableComponent(const Core::TransformComponent & transform, const Core::RenderableComponent & renderable)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static ShaderProgram shaderProgram("shader");
    shaderProgram.enable();

    static const auto id = loadTexture("assets/textures/checkerboard.png");
    glBindTexture(GL_TEXTURE_2D, id);

    glm::mat4 projection = glm::perspective(glm::radians(45.f), 1280.f / 720.f, 0.1f, 100.0f);
//    glm::mat4 projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);

    glm::mat4 view = glm::lookAt(
            glm::vec3(0,0,3), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    static float offset = 0.1f;
    glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.position);
    model = glm::scale(model, transform.scale);
    model = glm::rotate(model, static_cast<float>(transform.rotation.x * M_PI / 180.0f), glm::vec3{1, 0, 0});
    model = glm::rotate(model, static_cast<float>(transform.rotation.y * M_PI / 180.0f), glm::vec3{0, 1, 0});
    model = glm::rotate(model, static_cast<float>(transform.rotation.z * M_PI / 180.0f), glm::vec3{0, 0, 1});

    auto mvp = projection * view * model;
    shaderProgram.setUniformValue("MVP", mvp);

    renderable.mesh.enableForDrawing();
    glDrawArrays(GL_TRIANGLES, 0, renderable.mesh.verticesCount());
    renderable.mesh.disableForDrawing();

    shaderProgram.disable();
}

uint32_t loadTexture(std::string_view path)
{
    uint32_t textureId;

    int width;
    int height;
    int channels;

    stbi_set_flip_vertically_on_load(true);
    stbi_uc * data = stbi_load(path.data(), &width, &height, &channels, 0);

    if(data == nullptr)
        return 0;

    GLenum internalFormat = 0;
    GLenum dataFormat = 0;

    if (channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return textureId;
}

} // namespace ProtonEngine::Renderer
