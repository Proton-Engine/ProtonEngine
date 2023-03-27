/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "protonengine/core/entrypoint.h"
#include "protonengine/core/application.h"

#include <fmt/core.h>

class SandboxApplication : public ProtonEngine::Core::Application
{
public:
    void initialize() override
    {
    }
};

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char **argv)
{
    return std::make_unique<SandboxApplication>();
}

