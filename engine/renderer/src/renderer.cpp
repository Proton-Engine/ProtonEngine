/*
 * Copyright © 2022-2026. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/renderer/renderer.h"
#include "protonengine/common/event_bus.h"
#include "protonengine/common/logger.h"
#include "protonengine/renderer/irenderer.h"

#include "opengl/opengl_renderer.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "opengl/opengl_buffer.h"

#include <format>
#include <fstream>
#include <glm/gtx/hash.hpp>
#include <sstream>

#include <stdexcept>

namespace std
{
template <>
struct hash<ProtonEngine::Renderer::Vertex>
{
    size_t operator()(ProtonEngine::Renderer::Vertex const & vertex) const
    {
        return ((hash<glm::vec3>()(vertex.position) << 1 ^
                 (hash<glm::vec3>()(vertex.normal) << 1)) >>
                1) ^
               (hash<glm::vec2>()(vertex.texture) << 1);
    }
};
} // namespace std

namespace ProtonEngine::Renderer
{

namespace
{

[[nodiscard]] auto initializeRenderer(Renderer::RendererBackend rendererBackend) -> std::unique_ptr<IRenderer>
{
    PROTON_LOG_DEBUG("Initializing renderer");

    switch (rendererBackend)
    {
    case Renderer::RendererBackend::OPENGL:
        return std::make_unique<OpenGL::OpenGLRenderer>();
    }

    throw std::runtime_error("Invalid renderer backend");
}

[[nodiscard]] auto loadShaderSourceFromDisk(const std::string & fileName) -> std::string
{
    PROTON_LOG_DEBUG(std::format("Loading shader source from file: {}", fileName));

    std::ifstream fileStream(fileName);
    std::stringstream shaderSource;
    std::string line;

    while (std::getline(fileStream, line))
    {
        shaderSource << line << "\n";
    }

    return shaderSource.str();
}

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

Renderer::Renderer(RendererBackend rendererBackend) : m_renderer(initializeRenderer(rendererBackend)), m_uploadContext(m_renderer->getUploadContext())
{
}

/*
*    glEnableVertexAttribArray(0);
    glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
    glVertexAttribBinding(0, 0);

    glEnableVertexAttribArray(1);
    glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
    glVertexAttribBinding(1, 0);

    glEnableVertexAttribArray(2);
    glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texture));
    glVertexAttribBinding(2, 0);
 */

void Renderer::setWindowContext(ContextLoadFunction func)
{
    m_renderer->setWindowContext(func);

    const auto vertexSource = loadShaderSourceFromDisk("./assets/shaders/shader.vert");
    const auto fragmentSource = loadShaderSourceFromDisk("./assets/shaders/shader.frag");

    PipelineDescriptor pipelineDescriptor{VertexLayoutDescriptor{
                                              sizeof(Vertex),
                                              {VertexAttributeDescriptor{
                                                   .location = 0,
                                                   .format = VertexFormat::Float3,
                                                   .offset = offsetof(Vertex, position),
                                                   .binding = 0,

                                               },
                                               VertexAttributeDescriptor{
                                                   .location = 1,
                                                   .format = VertexFormat::Float3,
                                                   .offset = offsetof(Vertex, normal),
                                                   .binding = 0,
                                               },
                                               VertexAttributeDescriptor{
                                                   .location = 2,
                                                   .format = VertexFormat::Float2,
                                                   .offset = offsetof(Vertex, texture),
                                                   .binding = 0,

                                               }}},
                                          m_renderer->createShader({"shader", {
                                                                                  {ShaderType::Vertex, vertexSource},
                                                                                  {ShaderType::Fragment, fragmentSource},
                                                                              }})};

    m_pipeline = m_renderer->createPipeline(std::move(pipelineDescriptor));
    m_commandList = m_renderer->createCommandList();

    Common::EventBus::subscribeToEvent(Common::Event::WINDOW_RESIZE_EVENT, std::function([&](Common::Event, Common::WindowResizeEventContext context) {
                                           m_windowWidth = static_cast<float>(context.width);
                                           m_windowHeight = static_cast<float>(context.height);
                                           m_renderer->setViewport(0, 0, context.width, context.height);
                                       }));
}

void Renderer::addToRenderQueue(const Transform & transform, const Mesh & mesh, const Material & material)
{
    m_renderableObjects.emplace_back(transform, mesh, material);
}

void Renderer::addLight(const Transform & transform, const Light & light)
{
    m_lights.emplace_back(transform, light);
}

void Renderer::renderAllInQueue()
{
    m_commandList->begin();
    m_commandList->setPipeline(*m_pipeline);

    Lights lights{
        getPointLight(m_lights, m_view),
        getDirectionalLight(m_lights, m_view)};

    const auto lightsBuffer = m_renderer->createBuffer({BufferType::UNIFORM});
    m_uploadContext.uploadBuffer(*lightsBuffer, std::as_bytes(std::span{&lights, 1}), 0);

    const auto viewBuffer = m_renderer->createBuffer({BufferType::UNIFORM});
    UniformViewData viewData{m_view, m_projection};
    m_uploadContext.uploadBuffer(*viewBuffer, std::as_bytes(std::span{&viewData, 1}), 0);

    const auto frameDescriptorSet = m_renderer->createDescriptorSet(
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

        const auto materialBuffer = m_renderer->createBuffer({BufferType::UNIFORM});
        m_uploadContext.uploadBuffer(*materialBuffer, std::as_bytes(std::span{&material, 1}), 0);

        const auto sampler = m_renderer->createSampler({ScalingMode::LINEAR, WrappingMode::REPEAT});

        const auto modelBuffer = m_renderer->createBuffer({BufferType::UNIFORM});
        m_uploadContext.uploadBuffer(*modelBuffer, std::as_bytes(std::span{&model, 1}), 0);

        const auto descriptorSet = m_renderer->createDescriptorSet(
            {.buffers = {{0, *modelBuffer}, {2, *materialBuffer}},
             .textures = {{0, renderableObject.material.baseTexture}, {1, renderableObject.material.specularMap}},
             .samplers = {{0, *sampler}, {1, *sampler}}});

        m_commandList->bindDescriptorSet(*descriptorSet);
        m_commandList->setVertexBuffer(renderableObject.mesh.vertexBuffer());
        m_commandList->setIndexBuffer(renderableObject.mesh.indexBuffer());
        m_commandList->drawIndexed(renderableObject.mesh.indicesCount());
    }

    m_commandList->end();

    m_renderableObjects.clear();
    m_lights.clear();
}

void Renderer::setCamera(const Transform & transform, const Camera & camera)
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

    m_view = glm::lookAt(
        transform.position,
        transform.position + glm::normalize(cameraRotationOffset),
        glm::vec3(0, 1, 0));

    if (camera.projection == Camera::Projection::PERSPECTIVE)
    {
        m_projection = glm::perspective(glm::radians(camera.fieldOfView), m_windowWidth / m_windowHeight, camera.clippingPlaneNear,
                                        camera.clippingPlaneFar);
    }

    if (camera.projection == Camera::Projection::ORTHOGRAPHIC)
    {
        PROTON_LOG_ERROR("Orthographic projection not supported yet");
        throw std::runtime_error("Orthographic projection not supported yet");
    }
}

std::unique_ptr<ITexture> Renderer::createTextureFromImage(const Assets::Image & image)
{
    // TODO: Remove this hacky way of loading textures
    const TextureDescriptor descriptor{
        .width = static_cast<uint32_t>(image.getWidth()),
        .height = static_cast<uint32_t>(image.getHeight()),
        .format = image.getChannels() == 4 ? TextureFormat::RGBA8 : TextureFormat::RGB8,
    };

    auto texture = m_renderer->createTexture(descriptor);
    m_renderer->getUploadContext().uploadTexture(*texture, image);
    return texture;
}

Mesh Renderer::createMeshFromModel(const Assets::Model & model)
{
    std::vector<Vertex> rendererVertices;
    std::unordered_map<Vertex, uint32_t> unique_vertices;
    std::vector<uint32_t> indices;

    const auto & vertices = model.getVertices();
    const auto & normals = model.getNormals();
    const auto & textureCoordinates = model.getTextureCoordinates();
    const auto & faces = model.getFaces();

    for (const auto & face : faces)
    {
        for (size_t i = 0; i < 3; i++)
        {
            Vertex vertex{
                vertices[face.vertexIndex[i]],
                normals[face.normalIndex[i]],
                textureCoordinates[face.textureIndex[i]]};

            if (!unique_vertices.contains(vertex))
            {
                rendererVertices.emplace_back(vertex);
                unique_vertices[vertex] = static_cast<uint32_t>(rendererVertices.size() - 1);
            }

            indices.emplace_back(unique_vertices[vertex]);
        }
    }

    // TODO: write data using UploadContext and create a CommandList to actually do the rendering :)
    auto vertexBuffer = m_renderer->createBuffer({BufferType::VERTEX});
    auto indexBuffer = m_renderer->createBuffer({BufferType::INDEX});

    m_renderer->getUploadContext().uploadBuffer(*vertexBuffer, std::as_bytes(std::span(rendererVertices)), 0);
    m_renderer->getUploadContext().uploadBuffer(*indexBuffer, std::as_bytes(std::span(indices)), 0);

    return Mesh{std::move(vertexBuffer), std::move(indexBuffer), indices.size()};
}

auto Renderer::getDefaultTexture() -> ITexture &
{
    // TODO: Remove the statics here:
    static uint8_t data[3] = {255, 255, 255};
    static Assets::Image image{data, 1, 1, 3};
    static auto texture = createTextureFromImage(image);
    return *texture;
}

auto Renderer::getDefaultMaterial() -> Material
{
    return Material{glm::vec3(1.0f), getDefaultTexture(), glm::vec3(0.5f), getDefaultTexture(), 32.0f};
}

} // namespace ProtonEngine::Renderer
