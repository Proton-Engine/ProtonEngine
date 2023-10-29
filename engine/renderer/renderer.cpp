/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/renderer/renderer.h"
#include "protonengine/renderer/shader_program.h"
#include "protonengine/components/camera.h"

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include <stdexcept>

# define M_PI           3.14159265358979323846  /* pi */

namespace ProtonEngine::Renderer
{

void setWindowContext(ContextLoadFunction func)
{
    gladLoadGLLoader(func);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

static glm::mat4 projection{};
static glm::mat4 view{};

void setCamera(const Components::Transform & transform, const Components::Camera & camera)
{
    if(!camera.isMainCamera)
    {
        return;
    }

    view = glm::lookAt(
            transform.position,
            transform.position + glm::vec3{0, 0, -1},
            glm::vec3(0,1,0)
    );

    view = glm::rotate(view, static_cast<float>(transform.rotation.y * M_PI / 180.0f), glm::vec3{0, 1, 0});
    view = glm::rotate(view, static_cast<float>(transform.rotation.x * M_PI / 180.0f), glm::vec3{1, 0, 0});
    view = glm::rotate(view, static_cast<float>(transform.rotation.z * M_PI / 180.0f), glm::vec3{0, 0, 1});

    if(camera.projection == Components::Camera::Projection::PERSPECTIVE)
    {
        projection = glm::perspective(glm::radians(camera.fieldOfView), 1280.f / 720.f, camera.clippingPlaneNear,
                                      camera.clippingPlaneFar);
    }

    if(camera.projection == Components::Camera::Projection::ORTHOGRAPHIC)
    {
        throw std::runtime_error("Orthographic projection not supported yet");
    }
}

void renderRenderableComponent(const Components::Transform & transform, const Components::MeshRenderer & meshRenderer)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static ShaderProgram shaderProgram("shader");
    shaderProgram.enable();
    meshRenderer.texture.activate();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.position);
    model = glm::scale(model, transform.scale);
    model = glm::rotate(model, static_cast<float>(transform.rotation.y * M_PI / 180.0f), glm::vec3{0, 1, 0});
    model = glm::rotate(model, static_cast<float>(transform.rotation.x * M_PI / 180.0f), glm::vec3{1, 0, 0});
    model = glm::rotate(model, static_cast<float>(transform.rotation.z * M_PI / 180.0f), glm::vec3{0, 0, 1});

    auto mvp = projection * view * model;
    shaderProgram.setUniformValue("MVP", mvp);

    meshRenderer.mesh.enableForDrawing();
    glDrawArrays(GL_TRIANGLES, 0, meshRenderer.mesh.verticesCount());
    meshRenderer.mesh.disableForDrawing();

    shaderProgram.disable();
    meshRenderer.texture.deactivate();
}

Texture createTextureFromImage(const Assets::Image & image)
{
    return Texture(image);
}

} // namespace ProtonEngine::Renderer