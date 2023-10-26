/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/entrypoint.h"
#include "protonengine/core/application.h"
#include "protonengine/core/entity.h"
#include "protonengine/core/cube.h"
#include "protonengine/components/mesh_renderer.h"
#include "protonengine/core/asset_manager.h"

#include "protonengine/renderer/renderer.h"

class SandboxApplication : public ProtonEngine::Core::Application
{
public:
    void initialize() override
    {
        auto cube = getScene().addEntity("cube");
        static auto image = ProtonEngine::Core::AssetManager::readImageFromFile("assets/textures/checkerboard.png");
        static auto texture = ProtonEngine::Renderer::createTextureFromImage(image);
        cube.addComponent(ProtonEngine::Components::MeshRenderer{m_cube, texture});
    }

private:
    ProtonEngine::Core::Cube m_cube{};
};

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char **argv)
{
    return std::make_unique<SandboxApplication>();
}

