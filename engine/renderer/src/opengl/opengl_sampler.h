// Copyright © 2026. Proton Engine
// Licensed using the MIT license

#pragma once
#include "protonengine/renderer/isampler.h"

namespace ProtonEngine::Renderer::OpenGL
{

class OpenGLSampler : public ISampler
{
public:
    explicit OpenGLSampler(const SamplerDescriptor & descriptor);
    ~OpenGLSampler() override;

    void bind(uint32_t slot) const;

private:
    SamplerDescriptor m_descriptor;
    uint32_t m_samplerId;
};

} // namespace ProtonEngine::Renderer::OpenGL
