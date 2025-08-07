/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#include "scripts/camera_controller.h"
// #include "scripts/rotator.h"

#include "protonengine/core/application.h"
#include "protonengine/core/asset_manager.h"
#include "protonengine/core/entity.h"
#include "protonengine/core/entrypoint.h"

#include "protonengine/core/components/camera_component.h"
#include "protonengine/core/components/mesh_renderer.h"

#include "protonengine/renderer/renderer.h"
#include "protonengine/ui/debug_layer.h"

class SandboxApplication final : public ProtonEngine::Core::Application
{
public:
    void initialize() override
    {
        using namespace ProtonEngine;

        addLayer(std::make_unique<UserInterface::DebugLayer>());

        static const auto cubeModel = Core::AssetManager::loadModel("assets/models/cube.obj");
        static Renderer::Mesh cubeMesh{cubeModel.getVertices(), cubeModel.getNormals(), cubeModel.getTextureCoordinates()};

        static auto image = Core::AssetManager::readImageFromFile("assets/textures/checkerboard.png");
        static auto texture = Renderer::createTextureFromImage(image);

        auto camera = getScene().addEntity("MainCamera", Core::Components::TransformComponent{{0, 2, 5}, {0, 0, 0}, {1, 1, 1}});
        camera.addComponent(Core::Components::CameraComponent{Core::Components::CameraComponent::Projection::PERSPECTIVE, 0.1f, 100.0f, 60, true});
        camera.emplaceScript<CameraController>();

        auto floor = getScene().addEntity("Floor", Core::Components::TransformComponent{{0, 0, -5}, {0, 0, 0}, {2, 0.1, 5}});
        floor.emplaceComponent<Core::Components::MeshRenderer>(cubeMesh, texture);

        auto leftWall = getScene().addEntity("leftWall", Core::Components::TransformComponent{{-2, 2, -5}, {0, 0, 0}, {0.1, 2, 5}});
        leftWall.emplaceComponent<Core::Components::MeshRenderer>(cubeMesh, texture);

        auto rightWall = getScene().addEntity("rightWall", Core::Components::TransformComponent{{2, 2, -5}, {0, 0, 0}, {0.1, 2, 5}});
        rightWall.emplaceComponent<Core::Components::MeshRenderer>(cubeMesh, texture);

        auto backWall = getScene().addEntity("backWall", Core::Components::TransformComponent{{0, 2, -10}, {0, 0, 0}, {2, 2, 0.1}});
        backWall.emplaceComponent<Core::Components::MeshRenderer>(cubeMesh, texture);

        auto light = getScene().addEntity("light", Core::Components::TransformComponent{{1.5, 2, -5}, {0, 0, 0}, {0.1, 0.1, 0.1}});
        light.emplaceComponent<Core::Components::MeshRenderer>(cubeMesh, texture);
    }
};

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char ** argv)
{
    return std::make_unique<SandboxApplication>();
}
