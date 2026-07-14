/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include "protonengine/renderer/iupload_context.h"

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLUploadContext : public IUploadContext
{
public:
    OpenGLUploadContext() = default;
    ~OpenGLUploadContext() override = default;

    void uploadBuffer(const IBuffer & destination, std::span<const std::byte> data, int32_t offset) const override;
    void uploadTexture(const ITexture & texture, const Assets::Image & image) const override;
};

} // namespace ProtonEngine::Renderer::OpenGL