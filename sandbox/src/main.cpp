/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/entrypoint.h"
#include "protonengine/core/application.h"
#include "protonengine/core/entity.h"
#include "protonengine/core/components.h"
#include "protonengine/core/cube.h"

class SandboxApplication : public ProtonEngine::Core::Application
{
public:
    void initialize() override
    {
        auto cube = getScene().addEntity("cube");
        cube.addComponent(ProtonEngine::Core::RenderableComponent{m_cube});
    }

private:
    ProtonEngine::Core::Cube m_cube{};
};

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char **argv)
{
    return std::make_unique<SandboxApplication>();
}

