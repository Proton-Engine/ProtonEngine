/*
 * Copyright © 2023. Proton Engine
 * Licensed using the MIT license
 */
 
#pragma once

#include "../src/renderable_object.h"
#include "protonengine/renderer/irenderer.h"

#include <glm/glm.hpp>

#include <vector>

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLRenderer final : public IRenderer
{
public:
    ~OpenGLRenderer() override = default;

    void setWindowContext(ContextLoadFunction func) override;

    void addToRenderQueue(const Core::Components::Transform & transform, const Core::Components::MeshRenderer & meshRenderer) override;
    void renderAllInQueue() override;
    void setCamera(const Core::Components::Transform & transform, const Core::Components::Camera & camera) override;
    void update() override;
private:
    glm::mat4 projection{};
    glm::mat4 view{};

    std::vector<RenderableObject> m_renderableObjects;
};

} // namespace ProtonEngine::Renderer::OpenGL