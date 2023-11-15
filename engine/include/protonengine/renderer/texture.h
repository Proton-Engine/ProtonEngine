/*
 * Copyright © 2022-2023. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/proton_interface.h"
#include "protonengine/assets/image.h"

#include <cinttypes>
#include <string_view>

namespace ProtonEngine::Renderer
{

class PROTON_API Texture
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