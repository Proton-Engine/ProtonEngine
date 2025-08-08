/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/assets/export.h"
#include "protonengine/assets/image.h"
#include "protonengine/assets/model.h"

#include <string_view>

namespace ProtonEngine::Assets
{

class PROTONENGINE_ASSETS_EXPORT AssetManager
{
public:
    [[nodiscard]] static Image readImageFromFile(std::string_view path);
    [[nodiscard]] static Model loadModel(std::string_view path);

private:
    [[nodiscard]] static Model loadObjModel(std::string_view path);
};

} // namespace ProtonEngine::Assets