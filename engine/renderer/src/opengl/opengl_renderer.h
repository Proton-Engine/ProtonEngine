/*
 * Copyright © 2023-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/irenderer.h"

#include "irenderer_internal.h"
#include "renderable_object.h"

#include <glm/glm.hpp>

#include <vector>

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLRenderer final : public IRenderer, public IRendererInternal
{
public:
    ~OpenGLRenderer() override = default;

    void setWindowContext(ContextLoadFunction func) override;

    void addToRenderQueue(const Transform & transform, const Mesh & mesh, const Texture & texture, const Material & material) override;
    void renderAllInQueue() override;
    void setCamera(const Transform & transform, const Camera & camera) override;
    void update() override;
    [[nodiscard]] auto createBuffer(const std::vector<Vertex> & vertices, const std::vector<uint32_t> & indices) const noexcept -> std::unique_ptr<IBuffer> override;

private:
    glm::mat4 projection{};
    glm::mat4 view{};

    std::vector<RenderableObject> m_renderableObjects;
};

} // namespace ProtonEngine::Renderer::OpenGL