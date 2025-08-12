/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "protonengine/common/event_bus.h"
#include "protonengine/common/logger.h"
#include "protonengine/renderer/irenderer.h"

#include "opengl/opengl_renderer.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "opengl/buffer.h"

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
std::unique_ptr<IRenderer> g_renderer;
IRendererInternal * g_rendererInternal;
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
    g_rendererInternal = dynamic_cast<IRendererInternal *>(g_renderer.get());
    assert(g_rendererInternal && "Renderer backend should implement IRendererInternal");
    return *g_renderer;
}

Texture createTextureFromImage(const Assets::Image & image)
{
    return Texture(image);
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

    return Mesh(g_rendererInternal->createBuffer(rendererVertices, indices));
}

} // namespace ProtonEngine::Renderer
