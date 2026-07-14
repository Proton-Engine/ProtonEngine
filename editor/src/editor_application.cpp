/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "editor_application.h"

#include "layers/editor_view.h"
#include "layers/file_explorer.h"
#include "layers/menu_bar.h"
#include "layers/properties.h"
#include "layers/scene_hierarchy.h"
#include "protonengine/assets/asset_manager.h"
#include "protonengine/core/components/camera_component.h"
#include "protonengine/core/components/light_component.h"
#include "protonengine/core/components/mesh_renderer.h"
#include "protonengine/core/components/native_script.h"
#include "protonengine/ui/debug_layer.h"
#include "scripts/rotator.h"

using namespace ProtonEngine;

class Mover final : public ProtonEngine::Core::Components::NativeScript
{
public:
    explicit Mover(const ProtonEngine::Core::Entity & entity, float speed)
        : NativeScript(entity)
        , m_speed(speed)
    {
    }


protected:
    void onUpdate(float timestep) override
    {
        auto transform = getComponent<ProtonEngine::Core::Components::TransformComponent>();

        transform->transform.position.x += m_speed * timestep;

        if (transform->transform.position.x > 10 || transform->transform.position.x < -10)
        {
            m_speed *= -1;
        }
    }

private:
    float m_speed;
};

class DirectionalLightMover final : public ProtonEngine::Core::Components::NativeScript
{
public:
    explicit DirectionalLightMover(const ProtonEngine::Core::Entity & entity, float speed)
        : NativeScript(entity)
        , m_speed(speed)
    {
    }


protected:
    void onUpdate(float timestep) override
    {
        auto transform = getComponent<ProtonEngine::Core::Components::TransformComponent>();

        transform->transform.rotation.z -= m_speed * timestep;
    }

private:
    float m_speed;
};

ProtonEditor::SandboxApplication::SandboxApplication()
    : Application("Proton Editor")
{
}

void ProtonEditor::SandboxApplication::initialize()
{
    addLayer(std::make_unique<Layers::SceneHierarchyLayer>());
    addLayer(std::make_unique<Layers::FileExplorer>());
    addLayer(std::make_unique<Layers::EditorView>(renderer()));
    addLayer(std::make_unique<Layers::Properties>());
    addLayer(std::make_unique<Layers::MenuBar>());

#if 1
    static const auto cubeModel = Assets::AssetManager::loadModel("assets/models/cube.obj");
    static Renderer::Mesh cubeMesh = renderer().createMeshFromModel(cubeModel);

    static auto image = Assets::AssetManager::readImageFromFile("assets/textures/box.png");
    static auto texture = renderer().createTextureFromImage(image);

    static auto imageSpecular = Assets::AssetManager::readImageFromFile("assets/textures/box-specular.png");
    static auto textureSpecular = renderer().createTextureFromImage(imageSpecular);

    static Renderer::Material materialLight = renderer().getDefaultMaterial();
    static Renderer::Material materialCube{glm::vec3(1.0f), *texture, glm::vec3(1.0f), *textureSpecular, 32};

    auto camera = getScene().addEntity("MainCamera", Core::Components::TransformComponent{{0, 0, 10}, {0, 0, 0}, {1, 1, 1}});
    camera.addComponent(Core::Components::CameraComponent{Core::Components::CameraComponent::Projection::PERSPECTIVE, 0.1f, 100.0f, 60, true});

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
                cube.emplaceComponent<Core::Components::MeshRenderer>(cubeMesh, materialCube);
                cube.emplaceScript<Rotator>((x + y + z + 1) * 10);
            }
        }
    }

    auto light = getScene().addEntity("Light", Core::Components::TransformComponent{{0, 0, -9},
                                                                                    {0, 0, 0},
                                                                                    {0.5, 0.5, 0.5}});
    light.emplaceComponent<Core::Components::MeshRenderer>(cubeMesh, materialLight);
    light.emplaceComponent<Core::Components::LightComponent>(
        Renderer::Light{Renderer::LightType::POINT, glm::vec3(0, 0, 1), 32});
    light.emplaceScript<Mover>(2.5f);

    auto directionalLight = getScene().addEntity("DirectionalLight",
                                                 Core::Components::TransformComponent{{0, 0, 0},
                                                                                      {0, 0, -90},
                                                                                      {1, 1, 1}});
    directionalLight.emplaceComponent<Core::Components::LightComponent>(
        Renderer::Light{Renderer::LightType::DIRECTIONAL, glm::vec3(1, 0, 0)});
    directionalLight.emplaceScript<DirectionalLightMover>(10.0f);
#endif
}