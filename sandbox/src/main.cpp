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

#include "..\..\engine\include\protonengine\user_interface\debug_layer.h"
#include "protonengine/renderer/renderer.h"

class SandboxApplication final : public ProtonEngine::Core::Application
{
public:
    void initialize() override
    {
        using namespace ProtonEngine;

        addLayer(std::make_unique<UserInterface::DebugLayer>());

        static const auto cubeModel = Core::AssetManager::loadModel("assets/models/cube.obj");
        static Renderer::Mesh plantMesh{cubeModel.getVertices(), cubeModel.getNormals(), cubeModel.getTextureCoordinates()};

        static auto image = Core::AssetManager::readImageFromFile("assets/textures/checkerboard.jpg");
        static auto texture = Renderer::createTextureFromImage(image);

        auto camera = getScene().addEntity("MainCamera");
        camera.addComponent(Components::Camera{Components::Camera::Projection::PERSPECTIVE,
                                               0.1f, 100.0f, 60, true});
        camera.addScript<CameraController>();
        camera.getComponent<Components::Transform>()->position = glm::vec3{0, 0, 5};

        auto plant = getScene().addEntity("Plant");
        plant.addComponent(Components::MeshRenderer{plantMesh, texture});
        plant.addScript<Rotator>();
    }
};

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char ** argv)
{
    return std::make_unique<SandboxApplication>();
}
