/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/application.h"

#include <memory>

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    auto application = getProtonApplication(argc, argv);

    application->run();
}