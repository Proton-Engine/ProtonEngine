/*
 * Copyright © 2023-2026. Proton Engine
 * Licensed using the MIT license
 */

#include "opengl_renderer.h"

#include "opengl_buffer.h"
#include "opengl_descriptor_set.h"
#include "opengl_sampler.h"
#include "opengl_texture.h"
#include "protonengine/common/logger.h"
#include "protonengine/renderer/irenderer.h"
#include "shader_program.h"

#include "protonengine/common/event_bus.h"

#include <glad/gl.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <algorithm>
#include <format>
#include <functional>
#include <numbers>
#include <stdexcept>

namespace ProtonEngine::Renderer::OpenGL
{

namespace
{

struct alignas(16) UniformViewData
{
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};

struct alignas(16) OpenGlLight
{
    glm::vec4 position;
    glm::vec4 direction;
    glm::vec4 color;
};

struct alignas(16) Lights
{
    OpenGlLight pointLight;
    OpenGlLight directionalLight;
};

// layout (std140) struct Material {
//     vec3 baseColor;
//     vec3 specularColor;
//     float shininess;
// };
struct alignas(16) OpenGlMaterial
{
    glm::vec4 baseColor;
    glm::vec4 specularColor;
};

[[nodiscard]] auto getDirectionalLight(const std::vector<RenderableLight> & lights, const glm::mat4 & view) -> OpenGlLight
{
    const auto directionalLight =
        std::ranges::find_if(lights, [&](const auto & light) { return light.light.type == LightType::DIRECTIONAL; });

    if (directionalLight == lights.end())
    {
        return {};
    }

    auto rot = glm::rotate(glm::mat4(1.0f), directionalLight->transform.rotation.y * std::numbers::pi_v<float> / 180.0f, glm::vec3{0, 1, 0});
    rot = glm::rotate(rot, directionalLight->transform.rotation.x * std::numbers::pi_v<float> / 180.0f, glm::vec3{1, 0, 0});
    rot = glm::rotate(rot, directionalLight->transform.rotation.z * std::numbers::pi_v<float> / 180.0f, glm::vec3{0, 0, 1});
    const auto lightDirection = glm::vec3(view * rot * glm::vec4(0, 1, 0, 0));

    return {
        .position = glm::vec4(directionalLight->transform.position, 0),
        .direction = glm::vec4(lightDirection, 0),
        .color = glm::vec4(directionalLight->light.color, directionalLight->light.intensity)};
}

[[nodiscard]] auto getPointLight(const std::vector<RenderableLight> & lights, const glm::mat4 & view) -> OpenGlLight
{
    for (const auto & light : lights)
    {
        if (light.light.type != LightType::POINT)
        {
            continue;
        }

        return {
            .position = glm::vec4(light.transform.position, 0),
            .direction = view * glm::vec4(light.transform.position, 1.0f),
            .color = glm::vec4(light.light.color, light.light.intensity)};
    }
    return {};
}

} // namespace

uint32_t program;

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
    const auto version = gladLoadGL(func);
    if (version == 0)
    {
        PROTON_LOG_ERROR("Failed to initialize OpenGL context");
        throw std::runtime_error("Failed to initialize OpenGL context");
    }

    // TODO: Move to an initialize for the renderer
#ifndef __APPLE__
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);
#endif

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    m_commandList = std::make_unique<OpenGLCommandList>();

    Common::EventBus::subscribeToEvent(Common::Event::WINDOW_RESIZE_EVENT, std::function([&](Common::Event, Common::WindowResizeEventContext context) {
                                           windowWidth = static_cast<float>(context.width);
                                           windowHeight = static_cast<float>(context.height);

                                           glViewport(0, 0, context.width, context.height);
                                       }));
}

void OpenGLRenderer::addToRenderQueue(const Transform & transform, const Mesh & mesh, const Material & material)
{
    m_renderableObjects.emplace_back(transform, mesh, material);
}

void OpenGLRenderer::addLight(const Transform & transform, const Light & light)
{
    m_lights.emplace_back(transform, light);
}

void OpenGLRenderer::renderAllInQueue()
{
    static ShaderProgram shaderProgram("shader");
    program = shaderProgram.id();
    m_commandList->begin();
    shaderProgram.enable();

    auto & uploadContext = getUploadContext();

    Lights lights{
        getPointLight(m_lights, view),
        getDirectionalLight(m_lights, view)};

    const auto lightsBuffer = createBuffer({BufferType::UNIFORM});
    uploadContext.uploadBuffer(*lightsBuffer, std::as_bytes(std::span{&lights, 1}), 0);

    const auto viewBuffer = createBuffer({BufferType::UNIFORM});
    UniformViewData viewData{view, projection};
    uploadContext.uploadBuffer(*viewBuffer, std::as_bytes(std::span{&viewData, 1}), 0);

    const auto frameDescriptorSet = createDescriptorSet(
        {.buffers = {{1, *viewBuffer}, {3, *lightsBuffer}},
         .textures = {},
         .samplers = {}});
    m_commandList->bindDescriptorSet(*frameDescriptorSet);

    for (const auto & renderableObject : m_renderableObjects)
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), renderableObject.transform.position);
        model = glm::rotate(model, renderableObject.transform.rotation.y * std::numbers::pi_v<float> / 180.0f, glm::vec3{0, 1, 0});
        model = glm::rotate(model, renderableObject.transform.rotation.x * std::numbers::pi_v<float> / 180.0f, glm::vec3{1, 0, 0});
        model = glm::rotate(model, renderableObject.transform.rotation.z * std::numbers::pi_v<float> / 180.0f, glm::vec3{0, 0, 1});
        model = glm::scale(model, renderableObject.transform.scale);

        OpenGlMaterial material{
            .baseColor = glm::vec4(renderableObject.material.baseColor, 1.0f),
            .specularColor = glm::vec4(renderableObject.material.specularColor, renderableObject.material.shininess)};

        const auto materialBuffer = createBuffer({BufferType::UNIFORM});
        uploadContext.uploadBuffer(*materialBuffer, std::as_bytes(std::span{&material, 1}), 0);

        const auto sampler = createSampler({ScalingMode::LINEAR, WrappingMode::REPEAT});

        const auto modelBuffer = createBuffer({BufferType::UNIFORM});
        uploadContext.uploadBuffer(*modelBuffer, std::as_bytes(std::span{&model, 1}), 0);

        const auto descriptorSet = createDescriptorSet(
            {.buffers = {{0, *modelBuffer}, {2, *materialBuffer}},
             .textures = {{0, renderableObject.material.baseTexture}, {1, renderableObject.material.specularMap}},
             .samplers = {{0, *sampler}, {1, *sampler}}});

        m_commandList->bindDescriptorSet(*descriptorSet);
        m_commandList->setVertexBuffer(renderableObject.mesh.vertexBuffer());
        m_commandList->setPipeline();
        m_commandList->setIndexBuffer(renderableObject.mesh.indexBuffer());
        m_commandList->drawIndexed(renderableObject.mesh.indicesCount());
    }

    shaderProgram.disable();

    m_commandList->end();

    m_renderableObjects.clear();
    m_lights.clear();
}

void OpenGLRenderer::setCamera(const Transform & transform, const Camera & camera)
{
    if (!camera.isMainCamera)
    {
        return;
    }

    const auto yaw = transform.rotation.y - 90;
    const auto pitch = transform.rotation.x;

    glm::vec3 cameraRotationOffset;
    cameraRotationOffset.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraRotationOffset.y = sin(glm::radians(pitch));
    cameraRotationOffset.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    view = glm::lookAt(
        transform.position,
        transform.position + glm::normalize(cameraRotationOffset),
        glm::vec3(0, 1, 0));

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

auto OpenGLRenderer::createBuffer(const BufferDescriptor & descriptor) -> std::unique_ptr<IBuffer>
{
    return std::make_unique<Buffer>(descriptor);
}

auto OpenGLRenderer::createTexture(const TextureDescriptor & descriptor) -> std::unique_ptr<ITexture>
{
    return std::make_unique<OpenGLTexture>(descriptor);
}

auto OpenGLRenderer::createDescriptorSet(const DescriptorSetDescriptor & descriptor) -> std::unique_ptr<IDescriptorSet>
{
    return std::make_unique<OpenGLDescriptorSet>(descriptor);
}

auto OpenGLRenderer::createSampler(const SamplerDescriptor & descriptor) -> std::unique_ptr<ISampler>
{
    return std::make_unique<OpenGLSampler>(descriptor);
}

auto OpenGLRenderer::getUploadContext() -> IUploadContext &
{
    return m_uploadContext;
}

} // namespace ProtonEngine::Renderer::OpenGL