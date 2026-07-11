/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include <string>

namespace ProtonEngine::Core::Components
{

struct Tag
{
    std::string tag;

    explicit Tag(const std::string & tag) :
        tag(tag) {}

    Tag() = default;
};

} // namespace ProtonEngine::Core::Components