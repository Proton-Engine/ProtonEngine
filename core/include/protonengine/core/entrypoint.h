/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "application.h"

#include <memory>

std::unique_ptr<ProtonEngine::Core::Application> getProtonApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    auto application = getProtonApplication(argc, argv);
    application->initialize();

    while(true)
    {
        application->update();
    }
}