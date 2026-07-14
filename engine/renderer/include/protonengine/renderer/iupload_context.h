/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/assets/image.h"
#include "protonengine/renderer/ibuffer.h"
#include "protonengine/renderer/itexture.h"

#include <span>

namespace ProtonEngine::Renderer
{

class IUploadContext
{
public:
    IUploadContext() = default;
    virtual ~IUploadContext() = default;
    IUploadContext(IUploadContext &) = delete;
    IUploadContext(IUploadContext &&) = delete;
    IUploadContext & operator=(IUploadContext &) = delete;
    IUploadContext & operator=(IUploadContext &&) = delete;

    virtual void uploadBuffer(const IBuffer & destination, std::span<const std::byte> data, int32_t offset) const = 0;
    virtual void uploadTexture(const ITexture & texture, const Assets::Image & image) const = 0;
};

} // namespace ProtonEngine::Renderer