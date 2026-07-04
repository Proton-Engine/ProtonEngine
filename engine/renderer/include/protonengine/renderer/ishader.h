/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#pragma once

#include <string>
#include <vector>

namespace ProtonEngine::Renderer
{

enum class ShaderType
{
    Vertex,
    Fragment,
};

struct ShaderSource
{
    ShaderType type;
    std::string source;
};

struct ShaderDescriptor
{
    std::string name;
    std::vector<ShaderSource> sources;
};

class IShader
{
public:
    IShader() = default;
    virtual ~IShader() = default;
    IShader(IShader &) = delete;
    IShader(IShader &&) = delete;
    IShader & operator=(IShader &) = delete;
    IShader & operator=(IShader &&) = delete;
};

} // namespace ProtonEngine::Renderer