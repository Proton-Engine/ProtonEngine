/*
 * Copyright © 2023. Proton Engine
 * Licensed using the MIT license
 */
 
#pragma once

#include "protonengine/renderer/irenderer.h"
#include "renderer/renderable_object.h"

#include <glm/glm.hpp>

#include <vector>

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLRenderer final : public IRenderer
{
public:
    ~OpenGLRenderer() override = default;

    void setWindowContext(ContextLoadFunction func) override;

    void addToRenderQueue(const Components::Transform & transform, const Components::MeshRenderer & meshRenderer) override;
    void renderAllInQueue() override;
    void setCamera(const Components::Transform & transform, const Components::Camera & camera) override;
    void update() override;
private:
    glm::mat4 projection{};
    glm::mat4 view{};

    std::vector<RenderableObject> m_renderableObjects;
};

} // namespace ProtonEngine::Renderer::OpenGL