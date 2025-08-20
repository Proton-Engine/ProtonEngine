/*
 * Copyright © 2023-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_renderer.h"

#include "buffer.h"
#include "protonengine/common/logger.h"
#include "protonengine/renderer/irenderer.h"
#include "shader_program.h"

#include "protonengine/common/event_bus.h"

#include "glad/glad.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"

#include <format>
#include <functional>
#include <numbers>
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
        PROTON_LOG_TRACE(std::format("GL CALLBACK: type = {:#x}, severity = {:#x}, message = {}", type, severity, message));
        return;
    }

    std::string messageType = (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "");
    PROTON_LOG_ERROR(std::format("GL CALLBACK: {} type = {:#x}, severity = {:#x}, message = {}", messageType, type, severity, message));
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

    Common::EventBus::subscribeToEvent(Common::Event::WINDOW_RESIZE_EVENT, std::function([&](Common::Event, Common::WindowResizeEventContext context) {
                                           windowWidth = static_cast<float>(context.width);
                                           windowHeight = static_cast<float>(context.height);

                                           glViewport(0, 0, context.width, context.height);
                                       }));
}

void OpenGLRenderer::addToRenderQueue(const Transform & transform, const Mesh & mesh, const Texture & texture, const Material & material)
{
    m_renderableObjects.emplace_back(transform, mesh, texture, material);
}

void OpenGLRenderer::renderAllInQueue()
{
    static ShaderProgram shaderProgram("shader");

    for (const auto & renderableObject : m_renderableObjects)
    {
        shaderProgram.enable();
        shaderProgram.setUniformValue("lightPosition", glm::vec3(0, 2, -10));
        renderableObject.texture.activate();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), renderableObject.transform.position);
        model = glm::scale(model, renderableObject.transform.scale);
        model = glm::rotate(model, renderableObject.transform.rotation.y * std::numbers::pi_v<float> / 180.0f, glm::vec3{0, 1, 0});
        model = glm::rotate(model, renderableObject.transform.rotation.x * std::numbers::pi_v<float> / 180.0f, glm::vec3{1, 0, 0});
        model = glm::rotate(model, renderableObject.transform.rotation.z * std::numbers::pi_v<float> / 180.0f, glm::vec3{0, 0, 1});

        const auto normalModelMatrix = glm::transpose(glm::inverse(model));

        shaderProgram.setUniformValue("modelMatrix", model);
        shaderProgram.setUniformValue("projectionMatrix", projection);
        shaderProgram.setUniformValue("viewMatrix", view);
        shaderProgram.setUniformValue("normalModelMatrix", normalModelMatrix);

        shaderProgram.setUniformValue("material.baseColor", renderableObject.material.baseColor);
        shaderProgram.setUniformValue("material.specularColor", renderableObject.material.specularColor);
        shaderProgram.setUniformValue("material.shininess", renderableObject.material.shininess);

        renderableObject.mesh.enableForDrawing();
        glDrawElements(GL_TRIANGLES, renderableObject.mesh.indicesCount(), GL_UNSIGNED_INT, nullptr);
        renderableObject.mesh.disableForDrawing();

        shaderProgram.disable();
        renderableObject.texture.deactivate();
    }

    m_renderableObjects.clear();
}

void OpenGLRenderer::setCamera(const Transform & transform, const Camera & camera)
{
    if (!camera.isMainCamera)
    {
        return;
    }

    view = glm::lookAt(
        transform.position,
        transform.position + glm::vec3{0, 0, -1},
        glm::vec3(0, 1, 0));

    view = glm::rotate(view, transform.rotation.y * std::numbers::pi_v<float> / 180.0f, glm::vec3{0, 1, 0});
    view = glm::rotate(view, transform.rotation.x * std::numbers::pi_v<float> / 180.0f, glm::vec3{1, 0, 0});
    view = glm::rotate(view, transform.rotation.z * std::numbers::pi_v<float> / 180.0f, glm::vec3{0, 0, 1});

    if (camera.projection == Camera::Projection::PERSPECTIVE)
    {
        projection = glm::perspective(glm::radians(camera.fieldOfView), windowWidth / windowHeight, camera.clippingPlaneNear,
                                      camera.clippingPlaneFar);
    }

    if (camera.projection == Camera::Projection::ORTHOGRAPHIC)
    {
        PROTON_LOG_ERROR("Orthographic projection not supported yet");
        throw std::runtime_error("Orthographic projection not supported yet");
    }
}

void OpenGLRenderer::update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto OpenGLRenderer::createBuffer(const std::vector<Vertex> & vertices, const std::vector<uint32_t> & indices) const noexcept -> std::unique_ptr<IBuffer>
{
    return std::make_unique<Buffer>(vertices, indices);
}

} // namespace ProtonEngine::Renderer::OpenGL