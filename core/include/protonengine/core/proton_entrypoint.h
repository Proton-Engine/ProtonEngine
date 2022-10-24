/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#pragma once

#include "proton_application.h"

#include <memory>

std::unique_ptr<ProtonEngine::Core::ProtonApplication> getProtonApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    auto application = getProtonApplication(argc, argv);
}