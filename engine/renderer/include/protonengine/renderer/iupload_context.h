/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "ibuffer.h"
#include "itexture.h"
#include "protonengine/assets/image.h"

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

    virtual void uploadBuffer(const IBuffer & destination, std::span<const std::byte> data, uint16_t offset) = 0;
    virtual void uploadTexture(const ITexture & texture, const Assets::Image & image) = 0;
};

} // namespace ProtonEngine::Renderer