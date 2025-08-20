/*
 * Copyright © 2022-2025. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/assets/image.h"
#include "protonengine/renderer/export.h"

namespace ProtonEngine::Renderer
{

class PROTONENGINE_RENDERER_EXPORT Texture
{
public:
    explicit Texture(const Assets::Image & image);

    virtual ~Texture() = default;
    Texture(Texture &) = delete;
    Texture(Texture &&) = delete;
    Texture operator=(Texture &) = delete;
    Texture & operator=(Texture &&) = delete;

    void activate() const;
    void deactivate() const;

private:
    uint32_t m_textureId;
};

} // namespace ProtonEngine::Renderer