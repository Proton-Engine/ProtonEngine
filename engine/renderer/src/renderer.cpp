/*
 * Copyright © 2022-2026. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/common/event_bus.h"
#include "protonengine/common/logger.h"
#include "protonengine/renderer/irenderer.h"

#include "opengl/opengl_renderer.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "opengl/opengl_buffer.h"

#include <glm/gtx/hash.hpp>

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
std::unique_ptr<IRendererBackend> g_renderer;
} // namespace

auto initializeRenderer(RendererBackend rendererBackend) -> IRenderer &
{
    if (g_renderer)
    {
        PROTON_LOG_ERROR("Renderer already initialized");
        throw std::runtime_error("Renderer already initialized");
    }

    if (rendererBackend != RendererBackend::OPENGL)
    {
        PROTON_LOG_ERROR("Renderer backend other than OpenGL are not supported");
        throw std::runtime_error("Renderer backend other than OpenGL are not supported");
    }

    PROTON_LOG_DEBUG("Initializing renderer");
    g_renderer = std::make_unique<OpenGL::OpenGLRenderer>();
    return *g_renderer;
}

std::unique_ptr<ITexture> createTextureFromImage(const Assets::Image & image)
{
    // TODO: Remove this hacky way of loading textures
    const TextureDescriptor descriptor{
        .width = static_cast<uint32_t>(image.getWidth()),
        .height = static_cast<uint32_t>(image.getHeight()),
        .format = image.getChannels() == 4 ? TextureFormat::RGBA8 : TextureFormat::RGB8,
    };

    auto texture = g_renderer->createTexture(descriptor);
    g_renderer->getUploadContext().uploadTexture(*texture, image);
    return texture;
}

Mesh createMeshFromModel(const Assets::Model & model)
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
    auto vertexBuffer = g_renderer->createBuffer({BufferType::VERTEX});
    auto indexBuffer = g_renderer->createBuffer({BufferType::INDEX});

    g_renderer->getUploadContext().uploadBuffer(*vertexBuffer, std::as_bytes(std::span(rendererVertices)), 0);
    g_renderer->getUploadContext().uploadBuffer(*indexBuffer, std::as_bytes(std::span(indices)), 0);

    return Mesh{std::move(vertexBuffer), std::move(indexBuffer), indices.size()};
}

auto getDefaultTexture() -> ITexture &
{
    // TODO: Remove the statics here:
    static uint8_t data[3] = {255, 255, 255};
    static Assets::Image image{data, 1, 1, 3};
    static auto texture = createTextureFromImage(image);
    return *texture;
}

} // namespace ProtonEngine::Renderer
