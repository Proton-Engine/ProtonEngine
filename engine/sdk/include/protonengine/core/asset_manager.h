/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
 */

#pragma once

#include "protonengine/assets/image.h"
#include "protonengine/renderer/texture.h"

#include <string_view>

namespace ProtonEngine::Core
{

class AssetManager
{
public:
    [[nodiscard]] static Assets::Image readImageFromFile(std::string_view path);
private:
};

} // namespace ProtonEngine