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

    void uploadBuffer(const IBuffer & destination, std::span<const std::byte> source, uint16_t offset) override;
};

} // namespace ProtonEngine::Renderer::OpenGL