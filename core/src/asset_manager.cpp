/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#include "ProtonEngine/core/asset_manager.h"

#include <fmt/format.h>
#include <stb_image/stb_image.h>

#include <stdexcept>

namespace ProtonEngine::Core
{

Renderer::Texture AssetManager::loadTextureFromFile(std::string_view path)
{
    return Renderer::Texture(path);
}


Assets::Image AssetManager::readImageFromFile(std::string_view path)
{
    int width;
    int height;
    int channels;

    stbi_set_flip_vertically_on_load(true);
    stbi_uc * data = stbi_load(path.data(), &width, &height, &channels, 0);

    if(data == nullptr)
        throw std::runtime_error(fmt::format("Something went wrong when loading image at :{}\n", path));

    const auto image = Assets::Image(data, width, height, channels);

    stbi_image_free(data);

    return image;
}

} // namespace ProtonEngine::Core