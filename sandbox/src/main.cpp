/*
 * Copyright © 2022-2023. Tim Herreijgers
 * Licensed using the MIT license
 */

#include "scripts/rotator.h"
#include "scripts/camera_controller.h"

#include "protonengine/core/entrypoint.h"
#include "protonengine/core/application.h"
#include "protonengine/core/asset_manager.h"

#include "protonengine/components/mesh_renderer.h"
#include "protonengine/components/camera.h"

#include "protonengine/renderer/renderer.h"

class SandboxApplication : public ProtonEngine::Core::Application
{
public:
    void initialize() override
    {
        using namespace ProtonEngine;

        static const auto cubeModel = Core::AssetManager::loadModel("assets/models/indoor_plant.obj");
        static Renderer::Mesh cubeMesh{cubeModel.getVertices(), cubeModel.getTextureCoordinates()};

        static auto image = Core::AssetManager::readImageFromFile("assets/textures/indoor_plant.jpg");
        static auto texture = Renderer::createTextureFromImage(image);

        auto camera = getScene().addEntity("MainCamera");
        camera.addComponent(Components::Camera{Components::Camera::Projection::PERSPECTIVE,
                                               0.1f, 100.0f, 60, true});
        camera.addScript<CameraController>();
        camera.getComponent<Components::Transform>()->position = glm::vec3{0, 0, 5};

        auto cube = getScene().addEntity("Cube");
        cube.addComponent(Components::MeshRenderer{cubeMesh, texture});
        cube.addScript<Rotator>();
    }
};

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char **argv)
{
    return std::make_unique<SandboxApplication>();
}

