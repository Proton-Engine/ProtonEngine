/*
 * Copyright © 2023. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_renderer.h"

#include "protonengine/components/camera.h"
#include "protonengine/core/logger.h"
#include "protonengine/math/constants.h"
#include "protonengine/renderer/renderer.h"
#include "protonengine/renderer/shader_program.h"

#include "core/event_bus.h"

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include <fmt/core.h>

#include <stdexcept>

namespace ProtonEngine::Renderer::OpenGL
{

static float windowWidth;
static float windowHeight;

void GLAPIENTRY
    MessageCallback(GLenum /*source*/,
                    GLenum type,
                    GLuint /*id*/,
                    GLenum severity,
                    GLsizei /*length*/,
                    const GLchar * message,
                    const void * /*userParam*/)
{
    if (type != GL_DEBUG_TYPE_ERROR)
    {
        PROTON_LOG_TRACE(fmt::format("GL CALLBACK: type = {:#x}, severity = {:#x}, message = {}", type, severity, message));
        return;
    }

    std::string messageType = (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "");
    PROTON_LOG_ERROR(fmt::format("GL CALLBACK: {} type = {:#x}, severity = {:#x}, message = {}", messageType, type, severity, message));
}

void OpenGLRenderer::setWindowContext(ContextLoadFunction func)
{
    gladLoadGLLoader(func);

    // TODO: Move to an initialize for the renderer
#ifndef __APPLE__
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
#endif

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    Core::EventBus::subscribeToEvent(Core::Event::WINDOW_RESIZE_EVENT, std::function([&](Core::Event, Core::WindowResizeEventContext context) {
                                         windowWidth = static_cast<float>(context.width);
                                         windowHeight = static_cast<float>(context.height);

                                         glViewport(0, 0, context.width, context.height);
                                     }));
}

void OpenGLRenderer::addToRenderQueue(const Components::Transform & transform, const Components::MeshRenderer & meshRenderer)
{
    static ShaderProgram shaderProgram("shader");
    shaderProgram.enable();
    meshRenderer.texture.activate();

    glm::mat4 model = glm::translate(glm::mat4(1.0f), transform.position);
    model = glm::scale(model, transform.scale);
    model = glm::rotate(model, transform.rotation.y * Math::ConstantsFloat::pi / 180.0f, glm::vec3{0, 1, 0});
    model = glm::rotate(model, transform.rotation.x * Math::ConstantsFloat::pi / 180.0f, glm::vec3{1, 0, 0});
    model = glm::rotate(model, transform.rotation.z * Math::ConstantsFloat::pi / 180.0f, glm::vec3{0, 0, 1});

    const auto normalModelMatrix = glm::transpose(glm::inverse(model));

    shaderProgram.setUniformValue("modelMatrix", model);
    shaderProgram.setUniformValue("projectionMatrix", projection);
    shaderProgram.setUniformValue("viewMatrix", view);
    shaderProgram.setUniformValue("normalModelMatrix", normalModelMatrix);

    meshRenderer.mesh.enableForDrawing();
    glDrawArrays(GL_TRIANGLES, 0, meshRenderer.mesh.verticesCount());
    meshRenderer.mesh.disableForDrawing();

    shaderProgram.disable();
    meshRenderer.texture.deactivate();
}

void OpenGLRenderer::renderAllInQueue()
{
}

void OpenGLRenderer::setCamera(const Components::Transform & transform, const Components::Camera & camera)
{
    if (!camera.isMainCamera)
    {
        return;
    }

    view = glm::lookAt(
        transform.position,
        transform.position + glm::vec3{0, 0, -1},
        glm::vec3(0, 1, 0));

    view = glm::rotate(view, transform.rotation.y * Math::ConstantsFloat::pi / 180.0f, glm::vec3{0, 1, 0});
    view = glm::rotate(view, transform.rotation.x * Math::ConstantsFloat::pi / 180.0f, glm::vec3{1, 0, 0});
    view = glm::rotate(view, transform.rotation.z * Math::ConstantsFloat::pi / 180.0f, glm::vec3{0, 0, 1});

    if (camera.projection == Components::Camera::Projection::PERSPECTIVE)
    {
        projection = glm::perspective(glm::radians(camera.fieldOfView), windowWidth / windowHeight, camera.clippingPlaneNear,
                                      camera.clippingPlaneFar);
    }

    if (camera.projection == Components::Camera::Projection::ORTHOGRAPHIC)
    {
        throw std::runtime_error("Orthographic projection not supported yet");
    }
}

void OpenGLRenderer::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} // namespace ProtonEngine::Renderer::OpenGL