// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#pragma once

#include "protonengine/core/application.h"

namespace ProtonEditor
{

class SandboxApplication final : public ProtonEngine::Core::Application
{
public:
    SandboxApplication();

protected:
    void initialize() override;
};

} // namespace ProtonEditor