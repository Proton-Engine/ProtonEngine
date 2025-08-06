/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "scripts/camera_controller.h"
#include "scripts/rotator.h"

#include "protonengine/core/application.h"
#include "protonengine/core/asset_manager.h"
#include "protonengine/core/entrypoint.h"

#include "protonengine/core/components/camera.h"
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

        auto camera = getScene().addEntity("MainCamera", Core::Components::Transform{{0, 2, 5}, {0, 0, 0}, {1, 1, 1}});
        camera.addComponent(Core::Components::Camera{Core::Components::Camera::Projection::PERSPECTIVE,
                                               0.1f, 100.0f, 60, true});
        // camera.addScript<CameraController>();
        camera.addScript(std::make_unique<CameraController>());

        auto floor = getScene().addEntity("Floor", Core::Components::Transform{{0, 0, -5}, {0, 0, 0}, {2, 0.1, 5}});
        floor.addComponent(Core::Components::MeshRenderer{cubeMesh, texture});

        auto leftWall = getScene().addEntity("leftWall", Core::Components::Transform{{-2, 2, -5}, {0, 0, 0}, {0.1, 2, 5}});
        leftWall.addComponent(Core::Components::MeshRenderer{cubeMesh, texture});

        auto rightWall = getScene().addEntity("rightWall", Core::Components::Transform{{2, 2, -5}, {0, 0, 0}, {0.1, 2, 5}});
        rightWall.addComponent(Core::Components::MeshRenderer{cubeMesh, texture});

        auto backWall = getScene().addEntity("backWall", Core::Components::Transform{{0, 2, -10}, {0, 0, 0}, {2, 2, 0.1}});
        backWall.addComponent(Core::Components::MeshRenderer{cubeMesh, texture});

        auto light = getScene().addEntity("light", Core::Components::Transform{{1.5, 2, -5}, {0, 0, 0}, {0.1, 0.1, 0.1}});
        light.addComponent(Core::Components::MeshRenderer{cubeMesh, texture});
    }
};

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char ** argv)
{
    return std::make_unique<SandboxApplication>();
}
