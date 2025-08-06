/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/core/export.h"

#include "protonengine/assets/image.h"
#include "protonengine/assets/model.h"

#include <string_view>

namespace ProtonEngine::Core
{

class PROTONENGINE_CORE_EXPORT AssetManager
{
public:
    [[nodiscard]] static Assets::Image readImageFromFile(std::string_view path);
    [[nodiscard]] static Assets::Model loadModel(std::string_view path);

private:
    [[nodiscard]] static Assets::Model loadObjModel(std::string_view path);
};

} // namespace ProtonEngine::Core