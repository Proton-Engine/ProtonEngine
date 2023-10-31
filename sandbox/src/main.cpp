/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "scripts/rotator.h"

#include "protonengine/core/entrypoint.h"
#include "protonengine/core/application.h"
#include "protonengine/core/cube.h"
#include "protonengine/core/asset_manager.h"

#include "protonengine/components/mesh_renderer.h"
#include "protonengine/components/camera.h"
#include "protonengine/components/proton_script.h"

#include "protonengine/renderer/renderer.h"


class MyScript : public ProtonEngine::Components::ProtonScript
{
public:
    void onUpdate(float timestep) override
    {
        auto * transform = getComponent<ProtonEngine::Components::Transform>();

        if(getKeyState(ProtonEngine::Core::KeyCode::KEY_A) == ProtonEngine::Core::KeyState::PRESSED)
        {
            transform->position.x += static_cast<float>(5.0f * timestep);
        }

        if(getKeyState(ProtonEngine::Core::KeyCode::KEY_D) == ProtonEngine::Core::KeyState::PRESSED)
        {
            transform->position.x -= static_cast<float>(5.0f * timestep);
        }
    }
};

class SandboxApplication : public ProtonEngine::Core::Application
{
public:
    void initialize() override
    {
        using namespace ProtonEngine;

        auto camera = getScene().addEntity("MainCamera");
        camera.addComponent(Components::Camera{Components::Camera::Projection::PERSPECTIVE,
                                               0.1f, 100.0f, 60, true});
        camera.addScript<MyScript>();

        getScene().getEntityRegistry().get<Components::Transform>(camera.getHandle()).position = glm::vec3{0, 0, 3};
        getScene().getEntityRegistry().get<Components::Transform>(camera.getHandle()).rotation = glm::vec3{0, 0, 0};

        auto cube = getScene().addEntity("cube");
        static auto image = Core::AssetManager::readImageFromFile("assets/textures/checkerboard.png");
        static auto texture = Renderer::createTextureFromImage(image);

        cube.addComponent(Components::MeshRenderer{m_cube, texture});
        cube.addScript<Rotator>();
    }

private:
    ProtonEngine::Core::Cube m_cube{};
};

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char **argv)
{
    return std::make_unique<SandboxApplication>();
}

