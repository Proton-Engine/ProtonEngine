// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#include "editor_application.h"
#include "protonengine/core/entrypoint.h"

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char ** argv)
{
    return std::make_unique<ProtonEditor::SandboxApplication>();
}