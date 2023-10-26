/*
* Copyright © 2022 Tim Herreijgers
* Licensed using the MIT license
*/

#pragma once

#include "protonengine/assets/image.h"

#include <cinttypes>
#include <string_view>

namespace ProtonEngine::Renderer
{

class Texture
{
public:
    explicit Texture(const Assets::Image & image);

    virtual ~Texture() = default;
    Texture(Texture&) = delete;
    Texture(Texture&&) = default;
    Texture operator=(Texture&) = delete;
    Texture& operator=(Texture&&) = default;

    void activate() const;
    void deactivate() const;

private:
    uint32_t m_textureId;
};

} // namespace ProtonEngine::Renderer