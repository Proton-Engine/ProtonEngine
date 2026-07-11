/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "material.h"
#include "protonengine/assets/image.h"
#include "protonengine/assets/model.h"
#include "protonengine/export.h"
#include "protonengine/renderer/camera.h"
#include "protonengine/renderer/icommand_list.h"
#include "protonengine/renderer/irender_backend.h"
#include "protonengine/renderer/itexture.h"
#include "protonengine/renderer/light.h"
#include "protonengine/renderer/mesh.h"
#include "protonengine/renderer/renderable_object.h"
#include "protonengine/renderer/transform.h"
#include "renderable_light.h"

#include <glm/mat4x4.hpp>
#include <memory>

namespace ProtonEngine::Renderer
{

class PROTONENGINE_EXPORT Renderer
{
public:
    enum class RendererBackend
    {
        OPENGL
    };

    using ContextLoadFunction = void (*(*)(const char *))(void);

    Renderer(RendererBackend rendererBackend);
    ~Renderer() = default;
    Renderer(Renderer &) = delete;
    Renderer(Renderer &&) = delete;
    Renderer & operator=(Renderer &) = delete;
    Renderer & operator=(Renderer &&) = delete;

    void setWindowContext(ContextLoadFunction func);
    void addToRenderQueue(const Transform & transform, const Mesh & mesh, const Material & material);
    void addLight(const Transform & transform, const Light & light);
    void renderAllInQueue();
    void setCamera(const Transform & transform, const Camera & camera);

    [[nodiscard]] auto createTextureFromImage(const Assets::Image & image) -> std::unique_ptr<ITexture>;
    [[nodiscard]] auto createMeshFromModel(const Assets::Model & model) -> Mesh;
    [[nodiscard]] auto getDefaultTexture() -> ITexture &;
    [[nodiscard]] auto getDefaultMaterial() -> Material;

private:
    std::unique_ptr<IRenderBackend> m_renderer;
    std::unique_ptr<ICommandList> m_commandList;
    std::unique_ptr<IPipeline> m_pipeline;
    std::unique_ptr<ITexture> m_defaultTexture;
    IUploadContext & m_uploadContext;

    glm::mat4 m_projection{};
    glm::mat4 m_view{};

    float m_windowWidth{};
    float m_windowHeight{};

    std::vector<RenderableObject> m_renderableObjects;
    std::vector<RenderableLight> m_lights;
};

} // namespace ProtonEngine::Renderer
