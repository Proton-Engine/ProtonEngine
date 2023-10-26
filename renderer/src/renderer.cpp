/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/renderer/renderer.h"
#include "protonengine/renderer/shader_program.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

namespace ProtonEngine::Renderer
{

void setWindowContext(ContextLoadFunction func)
{
    gladLoadGLLoader(func);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void renderRenderableComponent(const Core::Components::Transform & transform, const Core::Components::MeshRenderer & meshRenderer)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static ShaderProgram shaderProgram("shader");
    shaderProgram.enable();
    meshRenderer.texture.activate();

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

    meshRenderer.mesh.enableForDrawing();
    glDrawArrays(GL_TRIANGLES, 0, meshRenderer.mesh.verticesCount());
    meshRenderer.mesh.disableForDrawing();

    shaderProgram.disable();
    meshRenderer.texture.deactivate();
}

Texture createTextureFromImage(const Core::Assets::Image & image)
{
    return Texture(image);
}

} // namespace ProtonEngine::Renderer
