/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "scripts/camera_controller.h"
#include "scripts/rotator.h"

#include "protonengine/assets/asset_manager.h"
#include "protonengine/core/application.h"
#include "protonengine/core/entity.h"
#include "protonengine/core/entrypoint.h"

#include "protonengine/core/components/camera_component.h"
#include "protonengine/core/components/mesh_renderer.h"
#include "protonengine/renderer/irenderer.h"

#include "protonengine/ui/debug_layer.h"

class SandboxApplication final : public ProtonEngine::Core::Application
{
public:
    void initialize() override
    {
        using namespace ProtonEngine;

        addLayer(std::make_unique<Ui::DebugLayer>());

        static const auto cubeModel = Assets::AssetManager::loadModel("assets/models/cube.obj");
        static Renderer::Mesh cubeMesh = Renderer::createMeshFromModel(cubeModel);

        static auto image = Assets::AssetManager::readImageFromFile("assets/textures/box.png");
        static auto texture = Renderer::createTextureFromImage(image);

        auto camera = getScene().addEntity("MainCamera", Core::Components::TransformComponent{{0, 2, 5}, {0, 0, 0}, {1, 1, 1}});
        camera.addComponent(Core::Components::CameraComponent{Core::Components::CameraComponent::Projection::PERSPECTIVE, 0.1f, 100.0f, 60, true});
        camera.emplaceScript<CameraController>();

        static constexpr auto distance = 4;

        static constexpr auto gridWidth = 3;
        static constexpr auto gridHeight = 3;
        static constexpr auto gridDepth = 3;

        static constexpr auto xStart = (gridWidth / 2) * distance * -1;
        static constexpr auto yStart = (gridHeight / 2) * distance * -1;
        static constexpr auto zStart = (gridDepth / 2) * distance - (gridDepth * distance + 5);

        for (auto x = 0; x < gridWidth; x++)
        {
            for (auto y = 0; y < gridHeight; y++)
            {
                for (auto z = 0; z < gridDepth; z++)
                {
                    auto cube = getScene().addEntity(std::format("Cube-{}-{}-{}", x, y, z),
                                                     Core::Components::TransformComponent{{xStart + distance * x, yStart + distance * y, zStart + distance * z},
                                                                                          {0, 0, 0},
                                                                                          {0.5, 0.5, 0.5}});
                    cube.emplaceComponent<Core::Components::MeshRenderer>(cubeMesh, texture);
                    cube.emplaceScript<Rotator>((x + y + z + 1) * 10);
                }
            }
        }
    }
};

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char ** argv)
{
    return std::make_unique<SandboxApplication>();
}
