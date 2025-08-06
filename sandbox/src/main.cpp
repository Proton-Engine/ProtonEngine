/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#include "scripts/camera_controller.h"
#include "scripts/rotator.h"

#include "protonengine/core/application.h"
#include "protonengine/core/asset_manager.h"
#include "protonengine/core/entrypoint.h"

#include "protonengine/components/camera.h"
#include "protonengine/components/mesh_renderer.h"

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

        auto camera = getScene().addEntity("MainCamera", Components::Transform{{0, 2, 5}, {0, 0, 0}, {1, 1, 1}});
        camera.addComponent(Components::Camera{Components::Camera::Projection::PERSPECTIVE,
                                               0.1f, 100.0f, 60, true});
        camera.addScript<CameraController>();

        auto floor = getScene().addEntity("Floor", Components::Transform{{0, 0, -5}, {0, 0, 0}, {2, 0.1, 5}});
        floor.addComponent(Components::MeshRenderer{cubeMesh, texture});

        auto leftWall = getScene().addEntity("leftWall", Components::Transform{{-2, 2, -5}, {0, 0, 0}, {0.1, 2, 5}});
        leftWall.addComponent(Components::MeshRenderer{cubeMesh, texture});

        auto rightWall = getScene().addEntity("rightWall", Components::Transform{{2, 2, -5}, {0, 0, 0}, {0.1, 2, 5}});
        rightWall.addComponent(Components::MeshRenderer{cubeMesh, texture});

        auto backWall = getScene().addEntity("backWall", Components::Transform{{0, 2, -10}, {0, 0, 0}, {2, 2, 0.1}});
        backWall.addComponent(Components::MeshRenderer{cubeMesh, texture});

        auto light = getScene().addEntity("light", Components::Transform{{1.5, 2, -5}, {0, 0, 0}, {0.1, 0.1, 0.1}});
        light.addComponent(Components::MeshRenderer{cubeMesh, texture});
    }
};

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char ** argv)
{
    return std::make_unique<SandboxApplication>();
}
